#ifndef LABARAT1_SMARTPTR_H
#define LABARAT1_SMARTPTR_H
#include <locale>
template<typename Type>
class SmartPTR{
private://пользователю по условию видеть не надо

    uint *count;
    Type *ptr;


public:

    template<typename u>
    friend class SmartPTR;


    SmartPTR();
    explicit SmartPTR(Type *ptr);
    SmartPTR(const SmartPTR<Type> & other);
    ~SmartPTR();


    template<typename u>
    SmartPTR<Type>& operator=(const SmartPTR<u>& other);


    SmartPTR<Type>& operator=(const SmartPTR<Type>& other);
    Type& operator*() const;
    Type* operator->() const;
    explicit operator bool() const;
    bool operator==(const SmartPTR<Type>& other) const;
    bool operator!=(const SmartPTR<Type>& other) const;
    bool operator==(std::nullptr_t) const;
    bool operator!=(std::nullptr_t) const ;
    uint getCount();


    void swap(SmartPTR<Type>& other);
    void reset();
    void reset(Type* pointer);
    void reset(SmartPTR<Type> smartptr);


private:

    void remove();

};


#include "Smartptr.tpp"

#endif //LABARAT1_SMARTPTR_H
