#include <iostream>

#include "ArrayGenerator.hpp"
#include "sort_tester_quick.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int max_size = 100000;
    ArrayGenerator generator(max_size);
    SortTesterQuick tester(generator);
    tester.run_experiments();
    std::cout << std::endl;
}
