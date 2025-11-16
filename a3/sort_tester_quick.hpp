#ifndef SORT_TESTER_QUICK_H
#define SORT_TESTER_QUICK_H

#include "ArrayGenerator.hpp"
#include "quick_sorter.hpp"

class SortTesterQuick {
public:
    explicit SortTesterQuick(const ArrayGenerator &generator);

    void run_experiments();

private:
    const ArrayGenerator &generator;
};

#endif
