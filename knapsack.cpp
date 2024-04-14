#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <random>
#include <string>
#include <vector>

#include "genetic_algorithms.hpp"

struct item
{
    item(int64_t value, int64_t weight) : value(value), weight(weight){};

    int64_t value;
    int64_t weight;
};

std::pair<int, int> greedy(std::vector<item> &items, int capacity)
{
    std::sort(items.begin(), items.end(), [](const item &a, const item &b)
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

int64_t fitness(const std::vector<int64_t> &genome, const std::vector<item> &items,
                int64_t capacity)
{
    int64_t value = 0;
    int64_t weight = 0;
    for (size_t i = 0; i < genome.size(); ++i)
    {
        value += genome[i] * items[i].value;
        weight += genome[i] * items[i].weight;
    }

    if (weight <= capacity)
        return value;
    else
        return -weight;
}

int main(int argc, const char **argv)
{
    if (argc != 5)
    {
        std::cerr
            << "USAGE: ./knapsack.x <n-items> <population-size> <generations> <mutation-rate>"
            << std::endl;
        return 1;
    }

    // generate random items
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int64_t> dist(1, 50);

    int64_t total_value = 0;
    int64_t total_weight = 0;
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

    int64_t capacity = total_weight * 0.75;
    std::cout << "capacity: " << capacity << std::endl;

    auto solution = greedy(items, capacity);
    std::cout << "************ GREEDY ****************" << std::endl;
    std::cout << "value: " << solution.first << std::endl;
    std::cout << "weight: " << solution.second << std::endl;

    // generate random initial population
    std::cout << "************ GENETIC ****************" << std::endl;
    size_t population_size = std::stoul(argv[2]);
    size_t generations = std::stoul(argv[3]);
    double mutation_rate = std::stod(argv[4]);

    // genetic solver
    ga<int64_t, int64_t> genetic_knapsack(population_size, num_of_items, {0, 1}, generations,
                                          problem_type::maximization);

    genetic_knapsack.generate_population(true);
    genetic_knapsack.evaluate_population(fitness, items, capacity);
    auto best_individual = genetic_knapsack.get_best_individual();
    int64_t value = 0;
    int64_t weight = 0;
    for (size_t i = 0; i < num_of_items; ++i)
    {
        value += best_individual[i] * items[i].value;
        weight += best_individual[i] * items[i].weight;
    }
    std::cout << "value: " << value << std::endl;
    std::cout << "weight: " << weight << std::endl;

    for (size_t g = 0; g < generations; ++g)
    {
        genetic_knapsack.tournament();
        genetic_knapsack.random_crossover();
        genetic_knapsack.random_mutate(mutation_rate);
        genetic_knapsack.evaluate_offsprings(fitness, items, capacity);
        genetic_knapsack.replace();
        genetic_knapsack.evaluate_population(fitness, items, capacity);
    }

    best_individual = genetic_knapsack.get_best_individual();
    value = 0;
    weight = 0;
    for (size_t i = 0; i < num_of_items; ++i)
    {
        value += best_individual[i] * items[i].value;
        weight += best_individual[i] * items[i].weight;
    }
    std::cout << "value: " << value << std::endl;
    std::cout << "weight: " << weight << std::endl;

    return 0;
}
