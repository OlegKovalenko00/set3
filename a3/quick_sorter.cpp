#include "quick_sorter.hpp"

#include <algorithm>
#include <cmath>

void QuickSorter::run_quick_sort(std::vector<int> &data, std::mt19937 &rng) {
    if (data.empty()) {
        return;
    }
    quick_sort_recursive(data, 0, static_cast<int>(data.size()), rng);
}

void QuickSorter::run_introsort(std::vector<int> &data, std::mt19937 &rng) {
    if (data.empty()) {
        return;
    }
    int n = static_cast<int>(data.size());
    int depth_limit = 0;
    if (n > 0) {
        depth_limit = 2 * static_cast<int>(std::log2(n));
    }
    introsort_recursive(data, 0, n, depth_limit, rng);
}

void QuickSorter::quick_sort_recursive(std::vector<int> &data,
                                       int left,
                                       int right,
                                       std::mt19937 &rng) {
    int length = right - left;
    if (length <= 1) {
        return;
    }
    int pivot_pos = partition_random(data, left, right, rng);
    quick_sort_recursive(data, left, pivot_pos, rng);
    quick_sort_recursive(data, pivot_pos + 1, right, rng);
}

int QuickSorter::partition_random(std::vector<int> &data,
                                  int left,
                                  int right,
                                  std::mt19937 &rng) {
    std::uniform_int_distribution<int> dist(left, right - 1);
    int pivot_index = dist(rng);
    int pivot_value = data[pivot_index];
    std::swap(data[pivot_index], data[right - 1]);
    int store_index = left;
    for (int i = left; i < right - 1; ++i) {
        if (data[i] < pivot_value) {
            std::swap(data[i], data[store_index]);
            ++store_index;
        }
    }
    std::swap(data[store_index], data[right - 1]);
    return store_index;
}

void QuickSorter::insertion_sort_range(std::vector<int> &data,
                                       int left,
                                       int right) {
    for (int i = left + 1; i < right; ++i) {
        int current = data[i];
        int j = i - 1;
        while (j >= left && data[j] > current) {
            data[j + 1] = data[j];
            --j;
        }
        data[j + 1] = current;
    }
}

void QuickSorter::heapify_range(std::vector<int> &data,
                                int left,
                                int heap_size,
                                int index) {
    int current = index;
    while (true) {
        int left_child = 2 * current + 1;
        int right_child = 2 * current + 2;
        int largest = current;

        if (left_child < heap_size &&
            data[left + left_child] > data[left + largest]) {
            largest = left_child;
        }
        if (right_child < heap_size &&
            data[left + right_child] > data[left + largest]) {
            largest = right_child;
        }
        if (largest == current) {
            break;
        }
        std::swap(data[left + current], data[left + largest]);
        current = largest;
    }
}

void QuickSorter::heap_sort_range(std::vector<int> &data,
                                  int left,
                                  int right) {
    int length = right - left;
    if (length <= 1) {
        return;
    }
    for (int i = length / 2 - 1; i >= 0; --i) {
        heapify_range(data, left, length, i);
    }
    for (int i = length - 1; i > 0; --i) {
        std::swap(data[left], data[left + i]);
        heapify_range(data, left, i, 0);
    }
}

void QuickSorter::introsort_recursive(std::vector<int> &data,
                                      int left,
                                      int right,
                                      int depth_limit,
                                      std::mt19937 &rng) {
    int length = right - left;
    if (length <= 1) {
        return;
    }
    if (length < 16) {
        insertion_sort_range(data, left, right);
        return;
    }
    if (depth_limit <= 0) {
        heap_sort_range(data, left, right);
        return;
    }
    int pivot_pos = partition_random(data, left, right, rng);
    introsort_recursive(data, left, pivot_pos, depth_limit - 1, rng);
    introsort_recursive(data, pivot_pos + 1, right, depth_limit - 1, rng);
}
