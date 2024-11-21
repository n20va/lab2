#include "tests.h"
#include "../Sequence/Sequence.h"
#include "../Sequence/ArraySequence/ArraySequence.h"
#include "../sorter/sorter.h"


compare_result compare(int a, int b) {
    if (a > b) {
        return first_is_bigger;
    } else if (a < b) {
        return first_is_smaller;
    } else {
        return equel;
    }
}
template <typename T>
void sort_test(Sequence<T> A, i_sorter<T> Ab, int len) {

    Ab.sort(A, len,ascending_sort);
    for (int i = 0; i<A.GetLength()-1; i++) {
       assert(A.Get(i)<=A.Get(i+1));
    }
}

void run_tests() {
    ArraySequence<int> A(new int [5]{3, 4, 42, 33, 15}, 5);
    bubble_sorter<int> Ab(compare);
    sort_test(A, Ab, A.GetLength());
}