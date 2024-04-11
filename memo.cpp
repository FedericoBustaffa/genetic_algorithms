#include <algorithm>
#include <chrono>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <utility>
#include <vector>

#include "item.hpp"

int brute_force(const std::vector<item>& items, int capacity, int n,
                std::map<std::pair<int64_t, int64_t>, int64_t>& memo)
{
    if (n == 0 || capacity == 0)
        return 0;

    if (items[n - 1].weight > capacity)
        return brute_force(items, capacity, n - 1, memo);

    std::pair<int64_t, int64_t> s(capacity, n);
    auto it = memo.find(s);
    if (it != memo.end())
        return it->second;

    int64_t value_picked =
        items[n - 1].value + brute_force(items, capacity - items[n - 1].weight, n - 1, memo);
    int64_t value_not_picked = brute_force(items, capacity, n - 1, memo);

    int64_t value_max = std::max(value_picked, value_not_picked);

    memo[s] = value_max;

    return value_max;
}

int main(int argc, const char** argv)
{
    if (argc != 2)
    {
        std::cerr << "USAGE: ./memo.x <n items>" << std::endl;
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

    // memoization
    std::map<std::pair<int64_t, int64_t>, int64_t> memo;

    auto start = std::chrono::high_resolution_clock::now();

    int64_t optimal_value = brute_force(items, capacity, (int)items.size(), memo);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "memoization brute force time: " << duration.count() << std::endl;

    std::cout << "optimal solution: " << optimal_value << std::endl;

    return 0;
}
