#include <fstream>
#include <iostream>
#include <random>
#include "../Sequence/ArraySequence/ArraySequence.h"
#include "tests.h"
#include "../sorter/sorter.h"
compare_result compare2(int a, int b) {
    if (a > b) {
        return first_is_bigger;
    } else if (a < b) {
        return first_is_smaller;
    } else {
        return equel;
    }
}

void bubble_sort(int test_size,
                 how_to_sort direction,
                 std::ofstream& array_sequence_results,
                 ArraySequence<int> array_sequence)
{
    bubble_sorter<int> sorter(compare2);

    auto start = std::chrono::high_resolution_clock::now();

    sorter.sort(array_sequence, array_sequence.GetLength(), direction);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration_array_sequence = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    array_sequence_results << test_size << "," << duration_array_sequence << ",bubble sort\n";
}
void run_performance_tests() {
    const int test_sizes[] = {10'000, 20'000, 50'000, 75'000, 100'000};
    std::ofstream array_sequence_results("../tests/results/results.csv");
    array_sequence_results << "Size,Time(ms),Sort type\n";

    std::random_device rd;
    std::mt19937 gen(rd());
    for (int size : test_sizes) {
        std::uniform_int_distribution<> distr(1, size*2);
        ArraySequence<int> array_sequence;

        for (int i = 0; i < size; ++i) {
            array_sequence.Append(distr(gen));
        }

        bubble_sort(size, ascending_sort, array_sequence_results, array_sequence);
        std::cout << "Bubble sort done for size " << size << std::endl;
    }
}