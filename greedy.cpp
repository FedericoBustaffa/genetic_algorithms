#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>

#include "item.hpp"

std::pair<int, int> greedy(std::vector<item>& items, int capacity)
{
    std::sort(items.begin(), items.end(), [](const item& a, const item& b)
              { return (double)a.value / a.weight > (double)b.value / b.weight; });

    int64_t weight = 0;
    int64_t value = 0;
    for (size_t i = 0; i < items.size(); ++i)
    {
        if (weight + items[i].weight <= capacity)
        {
            weight += items[i].weight;
            value += items[i].value;
        }
    }

    return {value, weight};
}

int main(int argc, const char** argv)
{
    if (argc != 2)
    {
        std::cerr << "USAGE: ./greedy.x <n items>" << std::endl;
        return 1;
    }

    std::default_random_engine engine(std::time(nullptr));
    std::uniform_int_distribution<int> dist(1, 50);

    int total_value = 0;
    int total_weight = 0;
    size_t num_of_items = std::stoul(argv[1]);
    std::vector<item> items;
    for (size_t i = 0; i < num_of_items; ++i)
    {
        items.push_back({dist(engine), dist(engine)});
        total_value += items[i].value;
        total_weight += items[i].weight;
    }

    std::cout << "total value: " << total_value << std::endl;
    std::cout << "total weight: " << total_weight << std::endl;

    int capacity = total_weight * 0.75;
    std::cout << "capacity: " << capacity << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    std::pair<int, int> solution = greedy(items, capacity);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "greedy value / weight time: " << duration.count() << std::endl;

    std::cout << "value: " << solution.first << std::endl;
    std::cout << "weight: " << solution.second << std::endl;

    return 0;
}
