#include "sort_tester_quick.hpp"

#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

SortTesterQuick::SortTesterQuick(const ArrayGenerator &generator)
    : generator(generator) {
}

void SortTesterQuick::run_experiments() {
    std::vector<ArrayGenerator::ArrayKind> kinds = {
        ArrayGenerator::ArrayKind::random_data,
        ArrayGenerator::ArrayKind::reversed_data,
        ArrayGenerator::ArrayKind::almost_sorted_data
    };

    int runs_per_case = 5;

    std::cout << "array_type,n,algorithm,run,time_micro" << std::endl;

    std::mt19937 rng(20251116);

    for (ArrayGenerator::ArrayKind kind : kinds) {
        std::string kind_str = ArrayGenerator::kind_name(kind);
        for (int size = 500; size <= 100000; size += 100) {
            for (int run_index = 1; run_index <= runs_per_case; ++run_index) {
                std::vector<int> base_data = generator.get_array(kind, size);

                std::vector<int> data_quick = base_data;
                auto start_quick = std::chrono::high_resolution_clock::now();
                QuickSorter::run_quick_sort(data_quick, rng);
                auto end_quick = std::chrono::high_resolution_clock::now();
                auto elapsed_quick = end_quick - start_quick;
                long long time_quick =
                    std::chrono::duration_cast<std::chrono::microseconds>(
                        elapsed_quick)
                        .count();

                std::cout << kind_str << ","
                          << size << ","
                          << "quick"
                          << ","
                          << run_index << ","
                          << time_quick << std::endl;

                std::vector<int> data_intro = base_data;
                auto start_intro = std::chrono::high_resolution_clock::now();
                QuickSorter::run_introsort(data_intro, rng);
                auto end_intro = std::chrono::high_resolution_clock::now();
                auto elapsed_intro = end_intro - start_intro;
                long long time_intro =
                    std::chrono::duration_cast<std::chrono::microseconds>(
                        elapsed_intro)
                        .count();

                std::cout << kind_str << ","
                          << size << ","
                          << "introsort"
                          << ","
                          << run_index << ","
                          << time_intro << std::endl;
            }
        }
    }
}
