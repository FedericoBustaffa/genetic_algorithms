#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>
#include <map>
#include <random>
#include <utility>
#include <vector>

#include "item.hpp"

int brute_force(const std::vector<item>& items, int capacity, int n,
                std::map<std::pair<int, int>, int>& memo)
{
    if (n == 0 || capacity == 0)
        return 0;

    if (items[n - 1].weight > capacity)
        return brute_force(items, capacity, n - 1, memo);

    std::pair<int, int> s(capacity, n);
    auto it = memo.find(s);
    if (it != memo.end())
        return it->second;

    int value_picked =
        items[n - 1].value + brute_force(items, capacity - items[n - 1].weight, n - 1, memo);
    int value_not_picked = brute_force(items, capacity, n - 1, memo);

    int value_max = std::max(value_picked, value_not_picked);

    memo[s] = value_max;

    return value_max;
}

int brute_force(const std::vector<item>& items, int capacity, int n)
{
    if (n == 0 || capacity == 0)
        return 0;

    if (items[n - 1].weight > capacity)
        return brute_force(items, capacity, n - 1);

    int value_picked =
        items[n - 1].value + brute_force(items, capacity - items[n - 1].weight, n - 1);
    int value_not_picked = brute_force(items, capacity, n - 1);

    int value_max = std::max(value_picked, value_not_picked);

    return value_max;
}

int main(int argc, const char** argv)
{
    std::default_random_engine engine(std::time(nullptr));
    std::uniform_int_distribution<int> dist(1, 50);

    int total_value = 0;
    int total_weight = 0;
    std::vector<item> items;
    for (size_t i = 0; i < 1000; ++i)
    {
        items.push_back({dist(engine), dist(engine)});
        total_value += items[i].value;
        total_weight += items[i].weight;
    }

    std::cout << "total value: " << total_value << std::endl;
    std::cout << "total weight: " << total_weight << std::endl;

    int capacity = total_weight * 0.75;
    std::cout << "capacity: " << capacity << std::endl;

    std::map<std::pair<int, int>, int> memo;
    auto start = std::chrono::high_resolution_clock::now();
    int solution = brute_force(items, capacity, (int)items.size(), memo);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "memo time: " << duration.count() << std::endl;
    std::cout << solution << std::endl;

    return 0;
}
