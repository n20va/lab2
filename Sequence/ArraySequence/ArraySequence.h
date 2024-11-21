#ifndef ARRAYSEQUENCE_H
#define ARRAYSEQUENCE_H

#include <stdexcept>
#include "../Sequence.h"
#include "DynamicArray.h"
#include "../../Smartptr/Smartptr.h"

template<typename T>
class ArraySequence : public Sequence<T> {
private:
    SmartPTR<DynamicArray<T>> array;
    int length;
public:
    ArraySequence() : array(nullptr), length(0) {
        array = SmartPTR(new DynamicArray<T>());
        length = 0;
    }

    ArraySequence(T* items, int length) : array(nullptr), length(0) {
        array = SmartPTR(new DynamicArray<T>(items, length));
        this->length = length;
    }

    ArraySequence(const ArraySequence<T>& other) : array(nullptr), length(0) {
        array = SmartPTR(new DynamicArray<T>(*other.array));
        this->length = other.length;
    }

    ~ArraySequence() = default;

    T& Get(int index) const override {
        if (index < 0 || index >= length) throw std::out_of_range("Index out of range");
        return array->Get(index);
    }

    void Set(T item, int index) override {
        if (index < 0 || index >= length) throw std::out_of_range("Index out of range");
        array->Set(item, index);
    }

    void Append(T item) override {
        if (length == array->GetCapacity()){
            array->Resize(array->GetCapacity() + 100);
        }

        array->Set(item, length);
        ++length;
    }

    void InsertAt(T item, int index) override {
        if (index < 0 || index > length) {
            throw std::out_of_range("Index out of range");
        }

        if (length == array->GetCapacity()) {
            array->Resize(array->GetCapacity() + 100);
        }

        if (index < length) {
            for (int i = length - 1; i >= index; --i) {
                array->Set(array->Get(i), i + 1);
            }
        }

        array->Set(item, index);
        ++length;
    }

    void RemoveAt(int index) override {
        array->RemoveAt(index);
        length--;
    }

    [[nodiscard]] uint GetLength() const override {
        return this->length;
    }

    void Clear() override {
        array->Clear();
        length = 0;
    }

    ArraySequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if (startIndex < 0 || endIndex > length || startIndex > endIndex) {
            throw std::out_of_range("Index out of range");
        }

        auto* newArray = new ArraySequence<T>();
        for (int i = startIndex; i < endIndex; ++i) {
            newArray->Append(Get(i));
        }
        return newArray;
    }
};

#endif // ARRAYSEQUENCE_H
