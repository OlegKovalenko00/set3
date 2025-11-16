#ifndef SORT_TESTER_H
#define SORT_TESTER_H

#include <vector>

#include "ArrayGenerator.hpp"

class SortTester {
public:
    explicit SortTester(const ArrayGenerator& generator);

    void run_experiments();

private:
    const ArrayGenerator& generator;

    static void insertion_sort_range(std::vector<int>& data, int left, int right);

    static void merge_ranges(std::vector<int>& data,
                             std::vector<int>& buffer,
                             int left,
                             int mid,
                             int right);

    static void merge_sort_recursive(std::vector<int>& data,
                                     std::vector<int>& buffer,
                                     int left,
                                     int right);

    static void merge_sort_hybrid_recursive(std::vector<int>& data,
                                            std::vector<int>& buffer,
                                            int left,
                                            int right,
                                            int threshold);

    static void run_merge_sort(std::vector<int>& data);

    static void run_hybrid_sort(std::vector<int>& data, int threshold);
};

#endif
