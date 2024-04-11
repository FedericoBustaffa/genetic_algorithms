#ifndef ITEM_HPP
#define ITEM_HPP

#include <cstdint>

struct item
{
    item(int64_t value, int64_t weight) : value(value), weight(weight){};

    int64_t value;
    int64_t weight;
};

#endif  // !ITEM_HPP
