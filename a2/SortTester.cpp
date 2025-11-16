#include "SortTester.hpp"

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

SortTester::SortTester(const ArrayGenerator& generator)
    : generator(generator) {
}

void SortTester::run_experiments() {
    std::vector<ArrayGenerator::ArrayKind> kinds = {
        ArrayGenerator::ArrayKind::random_data,
        ArrayGenerator::ArrayKind::reversed_data,
        ArrayGenerator::ArrayKind::almost_sorted_data
    };

    std::vector<int> thresholds = {0, 5, 10, 15, 20, 30, 50};
    int runs_per_case = 5;

    std::cout << "array_type,n,algorithm,threshold,run,time_micro" << std::endl;

    for (ArrayGenerator::ArrayKind kind : kinds) {
        std::string kind_str = ArrayGenerator::kind_name(kind);
        for (int size = 500; size <= 100000; size += 100) {
            for (int threshold : thresholds) {
                std::string algorithm_name = threshold == 0 ? "merge" : "hybrid";
                for (int run_index = 1; run_index <= runs_per_case; ++run_index) {
                    std::vector<int> data = generator.get_array(kind, size);

                    auto start_time = std::chrono::high_resolution_clock::now();
                    if (threshold == 0) {
                        run_merge_sort(data);
                    } else {
                        run_hybrid_sort(data, threshold);
                    }
                    auto finish_time = std::chrono::high_resolution_clock::now();
                    auto elapsed = finish_time - start_time;
                    long long micros =
                        std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

                    std::cout << kind_str << ","
                              << size << ","
                              << algorithm_name << ","
                              << threshold << ","
                              << run_index << ","
                              << micros << std::endl;
                }
            }
        }
    }
}

void SortTester::insertion_sort_range(std::vector<int>& data, int left, int right) {
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

void SortTester::merge_ranges(std::vector<int>& data,
                              std::vector<int>& buffer,
                              int left,
                              int mid,
                              int right) {
    int i = left;
    int j = mid;
    int k = left;

    while (i < mid && j < right) {
        if (data[i] <= data[j]) {
            buffer[k] = data[i];
            ++i;
        } else {
            buffer[k] = data[j];
            ++j;
        }
        ++k;
    }

    while (i < mid) {
        buffer[k] = data[i];
        ++i;
        ++k;
    }

    while (j < right) {
        buffer[k] = data[j];
        ++j;
        ++k;
    }

    for (int t = left; t < right; ++t) {
        data[t] = buffer[t];
    }
}

void SortTester::merge_sort_recursive(std::vector<int>& data,
                                      std::vector<int>& buffer,
                                      int left,
                                      int right) {
    int length = right - left;
    if (length <= 1) {
        return;
    }
    int mid = left + length / 2;
    merge_sort_recursive(data, buffer, left, mid);
    merge_sort_recursive(data, buffer, mid, right);
    merge_ranges(data, buffer, left, mid, right);
}

void SortTester::merge_sort_hybrid_recursive(std::vector<int>& data,
                                             std::vector<int>& buffer,
                                             int left,
                                             int right,
                                             int threshold) {
    int length = right - left;
    if (length <= 1) {
        return;
    }
    if (length <= threshold) {
        insertion_sort_range(data, left, right);
        return;
    }
    int mid = left + length / 2;
    merge_sort_hybrid_recursive(data, buffer, left, mid, threshold);
    merge_sort_hybrid_recursive(data, buffer, mid, right, threshold);
    merge_ranges(data, buffer, left, mid, right);
}

void SortTester::run_merge_sort(std::vector<int>& data) {
    if (data.empty()) {
        return;
    }
    std::vector<int> buffer(data.size());
    merge_sort_recursive(data, buffer, 0, static_cast<int>(data.size()));
}

void SortTester::run_hybrid_sort(std::vector<int>& data, int threshold) {
    if (data.empty()) {
        return;
    }
    std::vector<int> buffer(data.size());
    merge_sort_hybrid_recursive(data, buffer, 0, static_cast<int>(data.size()), threshold);
}
