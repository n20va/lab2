#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <stdexcept>

template <class T>
class Node {
public:
    T* data;
    Node<T>* next;
    explicit Node(T* data) : data(data), next(nullptr) {}
};

template <class T>
class LinkedList {
private:
    Node<T>* head;
    uint length;
public:
    explicit LinkedList() : head(nullptr), length(0) {}

    explicit LinkedList(T* items, int count) : head(nullptr), length(0) {
        for (int i = 0; i < count; ++i) {
            Append(items[i]);
        }
        delete[] items;
//        items = nullptr;
    }

    LinkedList(const LinkedList<T>& list) : head(nullptr), length(0) {
        Node<T>* current = list.head;
        while (current != nullptr) {
            Append(*(current->data));
            current = current->next;
        }
    }

    ~LinkedList() {
        Clear();
    }

    void Append(T& item) {
        T* dataCopy = new T(item);
        auto* newNode = new Node<T>(dataCopy);
        if (head == nullptr)
            head = newNode;
        else {
            Node<T>* current = head;
            while (current->next != nullptr)
                current = current->next;
            current->next = newNode;
        }
        length++;
    }

    void Prepend(T item) {
        T* dataCopy = new T(item);
        auto* newNode = new Node<T>(dataCopy);
        newNode->next = head;
        head = newNode;
        length++;
    }

    void InsertAt(T item, int index) {
        if (index < 0 || index > length)
            throw std::out_of_range("Index out of range");

        if (index == 0) {
            Prepend(item);
            return;
        }

        T* dataCopy = new T(item);
        auto* newNode = new Node<T>(dataCopy);
        Node<T>* current = head;
        for (int i = 0; i < index - 1; ++i)
            current = current->next;
        newNode->next = current->next;
        current->next = newNode;
        length++;
    }

    void RemoveAt(int index) {
        if (index < 0 || index >= length)
            throw std::out_of_range("Index out of range");

        if (index == 0) {
            Node<T>* temp = head;
            head = head->next;
            delete temp->data;
            delete temp;
            length--;
            return;
        }

        Node<T>* current = head;
        for (int i = 0; i < index - 1; ++i)
            current = current->next;

        Node<T>* temp = current->next;
        current->next = temp->next;
        delete temp->data;
        delete temp;
        length--;
    }

    T& Get(int index) const {
        if (index < 0 || index >= length)
            throw std::out_of_range("Index out of range");

        Node<T>* current = head;
        for (int i = 0; i < index; ++i)
            current = current->next;
        return *(current->data);
    }

    void Set(T item, int index) {
        if (index < 0 || index >= length)
            throw std::out_of_range("Index out of range");

        Node<T>* current = head;
        for (int i = 0; i < index; ++i)
            current = current->next;
        delete current->data;
        current->data = new T(item);
    }

    [[nodiscard]] uint GetLength() const {
        return length;
    }

    void Clear() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current->data;
            delete current;
            current = next;
        }
        head = nullptr;
        length = 0;
    }
};

#endif // LINKEDLIST_H
