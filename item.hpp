#ifndef ITEM_HPP
#define ITEM_HPP

struct item
{
    item(int value, int weight) : value(value), weight(weight){};

    int value;
    int weight;
};

#endif  // !ITEM_HPP
