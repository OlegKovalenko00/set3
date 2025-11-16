#ifndef ARRAY_GENERATOR_H
#define ARRAY_GENERATOR_H

#include <string>
#include <vector>

class ArrayGenerator {
public:
    enum class ArrayKind {
        random_data,
        reversed_data,
        almost_sorted_data
    };

    explicit ArrayGenerator(int max_size);

    std::vector<int> get_array(ArrayKind kind, int size) const;

    static std::string kind_name(ArrayKind kind);

private:
    int max_size;
    std::vector<int> random_base;
    std::vector<int> reversed_base;
    std::vector<int> almost_sorted_base;
};

#endif
