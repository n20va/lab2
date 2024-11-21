#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <locale>

template <typename T>
class Sequence
{
public:
    virtual T& Get(int index) const = 0;

    virtual void Append(T item) = 0;

    virtual void InsertAt(T item, int index) = 0;

    virtual void Set(T item, int index) = 0;

    virtual void RemoveAt(int index) = 0;

    [[nodiscard]] virtual uint GetLength() const = 0;

    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;

    virtual void Clear() = 0;

    virtual ~Sequence() = default;
};

#endif // SEQUENCE_H
