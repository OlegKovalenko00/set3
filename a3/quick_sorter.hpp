#ifndef QUICK_SORTER_H
#define QUICK_SORTER_H

#include <random>
#include <vector>

class QuickSorter {
public:
    static void run_quick_sort(std::vector<int> &data, std::mt19937 &rng);
    static void run_introsort(std::vector<int> &data, std::mt19937 &rng);

private:
    static void quick_sort_recursive(std::vector<int> &data,
                                     int left,
                                     int right,
                                     std::mt19937 &rng);

    static int partition_random(std::vector<int> &data,
                                int left,
                                int right,
                                std::mt19937 &rng);

    static void insertion_sort_range(std::vector<int> &data, int left, int right);

    static void heapify_range(std::vector<int> &data,
                              int left,
                              int heap_size,
                              int index);

    static void heap_sort_range(std::vector<int> &data, int left, int right);

    static void introsort_recursive(std::vector<int> &data,
                                    int left,
                                    int right,
                                    int depth_limit,
                                    std::mt19937 &rng);
};

#endif
