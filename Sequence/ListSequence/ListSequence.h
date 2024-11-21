#ifndef LIST_SEQ_H
#define LIST_SEQ_H

#include "../Sequence.h"
#include "LinkedList.h"
#include "../../SmartPtr/SmartPtr.h"

template <typename T>
class ListSequence : public Sequence<T> {
private:
    SmartPtr<LinkedList<T>> list;
public:
    ListSequence() {
        list = SmartPtr(new LinkedList<T>());
    }

    ListSequence(T* items, int length) {
        list = SmartPtr(new LinkedList<T>(items, length));
    }

    ListSequence(const ListSequence<T>& other) {
        list = SmartPtr(new LinkedList<T>(*other.list));
    }

    ListSequence<T>& operator=(const ListSequence<T>& other) {
        if (this != &other) {
            list = SmartPtr(new LinkedList<T>(*other.list));
        }
        return *this;
    }

    ~ListSequence() = default;

    void Append(T item) override {
        list->Append(item);
    }

    void InsertAt(T item, int index) override {
        list->InsertAt(item, index);
    }

    void RemoveAt(int index) override {
        list->RemoveAt(index);
    }

    T& Get(int index) const override {
        return list->Get(index);
    }

    void Set(T item, int index) override {
        list->Set(item, index);
    }

    [[nodiscard]] uint GetLength() const override {
        return list->GetLength();
    }

    void Clear() override {
        list->Clear();
    }

    ListSequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        // Проверка границ
        if (startIndex < 0 || endIndex > list->GetLength() || startIndex > endIndex) {
            throw std::out_of_range("Invalid index range");
        }

        // Создаем новый список для подпоследовательности
        auto* subsequence = new ListSequence<T>();

        // Копируем элементы в диапазоне [startIndex, endIndex]
        for (int i = startIndex; i < endIndex; ++i) {
            subsequence->Append(list->Get(i));
        }

        return subsequence;
    }
};

#endif // LIST_SEQ_H