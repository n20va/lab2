#ifndef SORTER_H
#define SORTER_H
#include "../Sequence/Sequence.h"

enum how_to_sort {
    descending_sort,
    ascending_sort
};

enum compare_result {
    equel,
    first_is_smaller,
    first_is_bigger
};

template <typename T>
class i_sorter {
protected:
    compare_result (*compare)(T a, T b);//указатель на функцию сравнения двух элементов
public:
    explicit i_sorter(compare_result (*compare)(T a, T b)) : compare(compare) {}
    virtual void sort(Sequence<T>& sequence, int len, how_to_sort how)=0;
    virtual ~i_sorter() = default;
};

template <typename T>
class bubble_sorter: public i_sorter<T>{
public:
    explicit bubble_sorter(compare_result (*compare)(T a, T b)) : i_sorter<T>(compare){}
    void sort(Sequence<T>& sequence, int len, how_to_sort how) override;
    ~bubble_sorter() override = default;
};
#include "sorter.tpp"
#endif //SORTER_H
