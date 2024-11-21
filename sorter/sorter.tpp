#include "sorter.h"
#include <utility>

template <typename T>
void bubble_sorter<T>::sort(Sequence<T>& sequence, int len, how_to_sort how) {
    bool swapped;
    for (int i = 0; i < len - 1; ++i) {
        swapped = false;
        for (int j = 0; j < len - i - 1; ++j) {
            T& a = sequence.Get(j);
            T& b = sequence.Get(j + 1);
            int comparison = (how == ascending_sort) ? this->compare(a, b) : this->compare(b, a);
            if (comparison == first_is_bigger) {
                std::swap(a, b);
                swapped = true;
            }
        }
        // Если не было обменов, сортировка завершена
        if (!swapped) {
            break;
        }
    }
}

template <typename T>
void batcher_sorter<T>::sort(Sequence<T>& sequence, int len, how_to_sort how) {
    auto compare_and_swap = [&](int i, int j) {
        T& a = sequence.Get(i);
        T& b = sequence.Get(j);
        int comparison = (how == ascending_sort) ? this->compare(a, b) : this->compare(b, a);
        if (comparison == first_is_bigger) {
            std::swap(a, b);
        }
    };

    // Схема Бэтчера для заданной длины len
    for (int width = 1; width < len; width *= 2) {
        for (int i = 0; i < len; i += 2 * width) {
            for (int j = i; j < i + width && j + width < len; ++j) {
                compare_and_swap(j, j + width);
            }
        }

        for (int width_gap = width / 2; width_gap > 0; width_gap /= 2) {
            for (int i = 0; i < len - width_gap; ++i) {
                if ((i / width) % 2 == 0) {
                    compare_and_swap(i, i + width_gap);
                }
            }
        }
    }
}

template <typename T>
void shell_sorter<T>::sort(Sequence<T>& sequence, int len, how_to_sort how) {
    // Генерация последовательности смещений
    std::vector<int> gaps;
    for (int gap = len / 2; gap > 0; gap /= 2) {
        gaps.push_back(gap);
    }

    // Сортировка с использованием смещений
    for (int gap : gaps) {
        for (int i = gap; i < len; ++i) {
            T temp = sequence.Get(i);
            int j = i;

            // Сравнение элементов с заданным смещением
            while (j >= gap) {
                T& a = sequence.Get(j - gap);
                T& b = temp;
                int comparison = (how == ascending_sort) ? this->compare(a, b) : this->compare(b, a);
                if (comparison == first_is_bigger) {
                    sequence.Set(j, a);
                    j -= gap;
                } else {
                    break;
                }
            }
            sequence.Set(j, temp);
        }
    }
}

template <typename T>
void insertion_sorter<T>::sort(Sequence<T>& sequence, int len, how_to_sort how) {
    for (int i = 1; i < len; ++i) {
        T key = sequence.Get(i);
        int j = i - 1;

        while (j >= 0) {
            T& a = sequence.Get(j);
            int comparison = (how == ascending_sort) ? this->compare(a, key) : this->compare(key, a);
            if (comparison == first_is_bigger) {
                sequence.Set(j + 1, a);
                --j;
            } else {
                break;
            }
        }
        sequence.Set(j + 1, key);
    }
}

template <typename T>
void selection_sorter<T>::sort(Sequence<T>& sequence, int len, how_to_sort how) {
    for (int i = 0; i < len - 1; ++i) {
        int extreme_index = i;
        for (int j = i + 1; j < len; ++j) {
            T& a = sequence.Get(extreme_index);
            T& b = sequence.Get(j);
            int comparison = (how == ascending_sort) ? this->compare(a, b) : this->compare(b, a);
            if (comparison == first_is_bigger) {
                extreme_index = j;
            }
        }
        if (extreme_index != i) {
            std::swap(sequence.Get(i), sequence.Get(extreme_index));
        }
    }
}

template <typename T>
void counting_sorter<T>::sort(Sequence<T>& sequence, int len, how_to_sort how) {
    if (len <= 0) return;

    T min_val = sequence.Get(0), max_val = sequence.Get(0);
    for (int i = 1; i < len; ++i) {
        T& val = sequence.Get(i);
        if (val < min_val) min_val = val;
        if (val > max_val) max_val = val;
    }

    std::vector<int> count(max_val - min_val + 1, 0);
    for (int i = 0; i < len; ++i) {
        count[sequence.Get(i) - min_val]++;
    }

    if (how == descending_sort) {
        for (int i = max_val - min_val, idx = 0; i >= 0; --i) {
            while (count[i]-- > 0) {
                sequence.Set(idx++, i + min_val);
            }
        }
    } else {
        for (int i = 0, idx = 0; i <= max_val - min_val; ++i) {
            while (count[i]-- > 0) {
                sequence.Set(idx++, i + min_val);
            }
        }
    }
}

template <typename T>
void binary_insertion_sorter<T>::sort(Sequence<T>& sequence, int len, how_to_sort how) {
    for (int i = 1; i < len; ++i) {
        T key = sequence.Get(i);
        int low = 0, high = i;

        while (low < high) {
            int mid = low + (high - low) / 2;
            T& mid_val = sequence.Get(mid);
            int comparison = (how == ascending_sort) ? this->compare(mid_val, key) : this->compare(key, mid_val);
            if (comparison == first_is_bigger) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        for (int j = i; j > low; --j) {
            sequence.Set(j, sequence.Get(j - 1));
        }
        sequence.Set(low, key);
    }
}

template <typename T>
void quadratic_selection_sorter<T>::sort(Sequence<T>& sequence, int len, how_to_sort how) {
    for (int i = 0; i < len / 2; ++i) {
        int min_index = i, max_index = len - i - 1;

        for (int j = i; j <= len - i - 1; ++j) {
            T& a = sequence.Get(min_index);
            T& b = sequence.Get(max_index);
            T& c = sequence.Get(j);

            if (this->compare(c, a) == first_is_smaller) min_index = j;
            if (this->compare(c, b) == first_is_bigger) max_index = j;
        }

        if (min_index != i) std::swap(sequence.Get(i), sequence.Get(min_index));
        if (max_index == i) max_index = min_index;
        if (max_index != len - i - 1) std::swap(sequence.Get(len - i - 1), sequence.Get(max_index));
    }
}

template <typename T>
void tree_selection_sorter<T>::sort(Sequence<T>& sequence, int len, how_to_sort how) {
    // Реализация через кучу
    std::multiset<T> tree(sequence.begin(), sequence.end());
    int idx = 0;

    if (how == ascending_sort) {
        for (auto& val : tree) {
            sequence.Set(idx++, val);
        }
    } else {
        for (auto it = tree.rbegin(); it != tree.rend(); ++it) {
            sequence.Set(idx++, *it);
        }
    }
}

template <typename T>
void merge_sorter<T>::sort(Sequence<T>& sequence, int len, how_to_sort how) {
    std::function<void(int, int)> merge_sort = [&](int left, int right) {
        if (left >= right) return;

        int mid = left + (right - left) / 2;
        merge_sort(left, mid);
        merge_sort(mid + 1, right);

        std::vector<T> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;

        while (i <= mid && j <= right) {
            T& a = sequence.Get(i);
            T& b = sequence.Get(j);
            int comparison = (how == ascending_sort) ? this->compare(a, b) : this->compare(b, a);

            temp[k++] = (comparison == first_is_smaller) ? sequence.Get(i++) : sequence.Get(j++);
        }
        while (i <= mid) temp[k++] = sequence.Get(i++);
        while (j <= right) temp[k++] = sequence.Get(j++);

        for (int t = 0; t < temp.size(); ++t) {
            sequence.Set(left + t, temp[t]);
        }
    };

    merge_sort(0, len - 1);
}

template <typename T>
void heap_sorter<T>::sort(Sequence<T>& sequence, int len, how_to_sort how) {
    auto heapify = [&](int n, int i) {
        int largest = i;
        int left = 2 * i + 1, right = 2 * i + 2;

        if (left < n && this->compare(sequence.Get(left), sequence.Get(largest)) == first_is_bigger) {
            largest = left;
        }
        if (right < n && this->compare(sequence.Get(right), sequence.Get(largest)) == first_is_bigger) {
            largest = right;
        }
        if (largest != i) {
            std::swap(sequence.Get(i), sequence.Get(largest));
            heapify(n, largest);
        }
    };

    for (int i = len / 2 - 1; i >= 0; --i) {
        heapify(len, i);
    }

    for (int i = len - 1; i > 0; --i) {
        std::swap(sequence.Get(0), sequence.Get(i));
        heapify(i, 0);
    }
}


template <typename T>
void quick_sorter<T>::sort(Sequence<T>& sequence, int len, how_to_sort how) {
    std::function<void(int, int)> quick_sort = [&](int low, int high) {
        if (low >= high) return;

        T pivot = sequence.Get(high);
        int left = low, right = high - 1;

        while (left <= right) {
            while (left <= right && this->compare(sequence.Get(left), pivot) != first_is_bigger) ++left;
            while (left <= right && this->compare(sequence.Get(right), pivot) != first_is_smaller) --right;

            if (left < right) {
                std::swap(sequence.Get(left), sequence.Get(right));
            }
        }

        std::swap(sequence.Get(left), sequence.Get(high));
        quick_sort(low, left - 1);
        quick_sort(left + 1, high);
    };

    quick_sort(0, len - 1);
}

