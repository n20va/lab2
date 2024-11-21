#ifndef LABARAT1_SMARTPTR_TPP
#define LABARAT1_SMARTPTR_TPP
#include "Smartptr.h"


template<typename Type>
SmartPTR<Type>::SmartPTR():ptr(nullptr), count(new uint (0)){};


template<typename Type>
SmartPTR<Type>::SmartPTR(Type *ptr): ptr(ptr), count(new uint (1)){};


template<typename Type>
SmartPTR<Type>::SmartPTR(const SmartPTR<Type> & other): ptr(other.ptr), count(other.count){
    ++(*count);
};


template<typename Type>
SmartPTR<Type>::~SmartPTR(){
    remove();
};


template<typename Type>
template<typename u>
SmartPTR<Type>& SmartPTR<Type>::operator=(const SmartPTR<u>& other) {
    if (ptr != other.ptr && count != other.count) {
        remove();
        if constexpr (std::is_polymorphic_v<u>) {
            ptr = dynamic_cast<Type*>(other.ptr);
        } else {
            ptr = static_cast<Type*>(other.ptr);
        }
        count = other.count;
        if (count) {
            ++(*count);
        }
    }
    return *this;
}


template<typename Type>
SmartPTR<Type>& SmartPTR<Type>::operator=(const SmartPTR<Type>& other) {
        if (this != &other) {
            if (ptr != other.ptr && count != other.count) {
                remove();
                ptr = other.ptr;
                count = other.count;
                if (count) {
                    ++(*count);
                }
            }
        }
        return *this;
    }


template<typename Type>
Type& SmartPTR<Type>::operator*() const {//разыменовываем и передаем по ссылке значение
    if (not ptr){
        throw std::runtime_error("Attempt to dereference a pointer that is currently nullptr");
    }
    return *ptr;
};


template<typename Type>
Type* SmartPTR<Type>::operator->() const {
    if (not ptr){
        throw std::runtime_error("Trying to dereference a pointer that is nullptr");
    }
    return ptr;
};


template<typename Type>
SmartPTR<Type>::operator bool() const{//когда надо конвертировать умный указатель в бул
    return ptr != nullptr;
};


template<typename Type>
bool SmartPTR<Type>::operator==(const SmartPTR<Type>& other) const{
    return ptr == other.ptr;
};


template<typename Type>
bool SmartPTR<Type>::operator!=(const SmartPTR<Type>& other) const{
    return ptr != other.ptr;
};


template<typename Type>
bool SmartPTR<Type>::operator==(std::nullptr_t) const {
    return ptr == nullptr;
};


template<typename Type>
bool SmartPTR<Type>::operator!=(std::nullptr_t) const {
    return ptr != nullptr;
};


template<typename Type>
uint SmartPTR<Type>::getCount(){
    if (not count){
        throw std::runtime_error("count = nullptr");
    }
    return *count;
};


template<typename Type>
void SmartPTR<Type>::swap(SmartPTR<Type>& other){
    Type* temp_ptr = std::move(ptr);//избежали копировани и ускорили
    uint* temp_count = count;//тривиальное копирование
    ptr = std::move(other.ptr);
    count = other.count;
    other.ptr = std::move(temp_ptr);
    other.count = temp_count;
};


template<typename Type>
void SmartPTR<Type>::reset(){
    remove();
    ptr = nullptr;
    count = new uint(0);
};


template<typename Type>
void SmartPTR<Type>::reset(Type* pointer){
    remove();
    ptr = pointer;
    count = new uint(1);
};


template<typename Type>
void SmartPTR<Type>::reset(SmartPTR<Type> smartptr){
    remove();
    ptr = smartptr.ptr;
    count = smartptr.count;
    ++count;
};


template<typename Type>
void SmartPTR<Type>::remove(){
    if (*count>0) {
        --(*count);
    }
    if ((*count)==0){
        delete ptr;
        delete count;
        ptr = nullptr;
        count = nullptr;
    }
};



#endif //LABARAT1_SMARTPTR_TPP