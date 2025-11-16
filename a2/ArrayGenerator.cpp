#include "ArrayGenerator.hpp"

#include <algorithm>
#include <random>

ArrayGenerator::ArrayGenerator(int max_size)
    : max_size(max_size),
      random_base(max_size),
      reversed_base(max_size),
      almost_sorted_base(max_size) {
    std::mt19937 rng(20251116);
    std::uniform_int_distribution<int> value_dist(0, 6000);

    for (int i = 0; i < max_size; ++i) {
        random_base[i] = value_dist(rng);
    }

    std::vector<int> sorted_base = random_base;
    std::sort(sorted_base.begin(), sorted_base.end());
    reversed_base = sorted_base;
    std::reverse(reversed_base.begin(), reversed_base.end());

    almost_sorted_base = sorted_base;
    int swap_count = max_size / 100;
    if (swap_count < 1) {
        swap_count = 1;
    }
    std::uniform_int_distribution<int> index_dist(0, max_size - 1);
    for (int i = 0; i < swap_count; ++i) {
        int a = index_dist(rng);
        int b = index_dist(rng);
        std::swap(almost_sorted_base[a], almost_sorted_base[b]);
    }
}

std::vector<int> ArrayGenerator::get_array(ArrayKind kind, int size) const {
    const std::vector<int>* source = nullptr;
    if (kind == ArrayKind::random_data) {
        source = &random_base;
    } else if (kind == ArrayKind::reversed_data) {
        source = &reversed_base;
    } else {
        source = &almost_sorted_base;
    }
    return std::vector<int>(source->begin(), source->begin() + size);
}

std::string ArrayGenerator::kind_name(ArrayKind kind) {
    if (kind == ArrayKind::random_data) {
        return "random";
    }
    if (kind == ArrayKind::reversed_data) {
        return "reversed";
    }
    return "almost_sorted";
}
