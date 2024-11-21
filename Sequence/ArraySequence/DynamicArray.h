#ifndef DYN_ARR_H
#define DYN_ARR_H

#include <iostream>
#include <cstring>

template <typename T>
class DynamicArray {
private:
    T* data;
    int capacity;
public:
    explicit DynamicArray<T>() : data(nullptr), capacity(100) {
        data = new T[100];
        capacity = 100;
    }

    explicit DynamicArray<T>(T* data, int capacity) : data(nullptr), capacity(capacity) {
        this->data = new T[100*(capacity/100 + 1)];
        memcpy(this->data, data, capacity * sizeof(T));
        this->capacity = capacity;
        delete[] data;
    }

    DynamicArray(const DynamicArray<T>& other) : data(nullptr), capacity(0) {
        capacity = other.capacity;
        if (capacity > 0) {
            data = new T[capacity];
            memcpy(data, other.data, capacity * sizeof(T));
        } else {
            data = nullptr;
        }
    }

    DynamicArray<T>& operator=(const DynamicArray<T>& other) {
        if (this != &other) {
            delete[] data;
            data = new T[other.capacity];
            for (int i = 0; i < other.capacity; ++i) {
                data[i] = other.data[i];
            }
            capacity = other.capacity;
        }
        return *this;
    }

    ~DynamicArray(){
        delete[] data;
        data = nullptr;
    }

    void Resize(int newCapacity) {
        T* newData = new T[newCapacity];
        memcpy(newData, data, capacity * sizeof(T));
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }


    T& Get(int index) {
        if (data == nullptr) {
            throw std::logic_error("Array is empty");
        }

        if (index < 0 || index >= capacity) {
            throw std::out_of_range("Index out of range");
        }

        return data[index];
    }

    void Set(T item, int index) {
        if (data == nullptr) {
            throw std::logic_error("Array is empty");
        }

        if (index < 0 || index >= capacity) {
            throw std::out_of_range("Index out of range");
        }

        data[index] = item;
    }

    void RemoveAt(int index) {
        if (data == nullptr) {
            throw std::logic_error("Array is empty");
        }

        if (index < 0 || index >= capacity) {
            throw std::out_of_range("Index out of range");
        }

        for (int i = index; i < capacity; ++i) {
            data[i] = data[i + 1];
        }
    }

    [[nodiscard]] virtual int GetCapacity() {
        return capacity;
    }

    void Clear() {
        delete[] data;
        data = nullptr;
        capacity = 0;
    }
};

#endif //DYN_ARR_H
