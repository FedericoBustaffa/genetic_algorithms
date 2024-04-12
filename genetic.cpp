#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <ostream>
#include <random>
#include <string>
#include <vector>

#include "crossover.hpp"
#include "individual.hpp"
#include "item.hpp"
#include "mutation.hpp"
#include "replacement.hpp"
#include "selection.hpp"
#include "spawn.hpp"

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

int64_t fitness(const std::vector<int> &genome, const std::vector<item> &items, size_t capacity)
{
    int64_t value = 0;
    int64_t weight = 0;
    for (size_t i = 0; i < genome.size(); ++i)
    {
        value += genome[i] * items[i].value;
        weight += genome[i] * items[i].weight;
    }

    if (weight <= (int64_t)capacity)
        return value;
    else
        return -weight;
}

int main(int argc, const char **argv)
{
    if (argc != 5)
    {
        std::cerr << "USAGE: ./genetic.x <n-items> <population-size> <generations> <mutation-rate>"
                  << std::endl;
        return 1;
    }

    // generate random items
    std::default_random_engine engine(std::time(nullptr));
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
    std::vector<individual<int, int64_t>> population =
        generate_population<int, int64_t>(population_size, num_of_items, {0, 1}, engine);

    for (size_t i = 0; i < population_size; ++i)
        population[i].set_fitness(fitness(population[i].get_genome(), items, capacity));
    std::sort(population.rbegin(), population.rend());
    individual<int, int64_t> best_individual = population[0];
    std::cout << "first: " << best_individual.get_fitness() << std::endl;

    size_t generations = std::stoul(argv[3]);
    double mutation_rate = std::stod(argv[4]);

    std::vector<size_t> parents;
    std::vector<individual<int, int64_t>> children;
    for (size_t g = 0; g < generations; ++g)
    {
        // selection
        parents = tournament<int, int64_t>(population, engine);

        // crossover
        children = one_point<int, int64_t>(population, parents, num_of_items, engine);

        // mutation
        stochastic_mutation<int, int64_t>(children, {0, 1}, num_of_items, mutation_rate, engine);

        // compute children fitness
        for (size_t i = 0; i < population_size; ++i)
            children[i].set_fitness(fitness(children[i].get_genome(), items, capacity));

        // replacement
        // population = replacement<int, int64_t>(population, children);
        population = children;

        // for (const auto &i : population)
        //     std::cout << i.get_fitness() << std::endl;

        if (population[0] > best_individual)
            best_individual = population[0];
    }

    std::cout << "fitness: " << best_individual.get_fitness() << std::endl;
    total_value = 0;
    total_weight = 0;
    for (size_t i = 0; i < num_of_items; ++i)
    {
        total_value += best_individual[i] * items[i].value;
        total_weight += best_individual[i] * items[i].weight;
    }

    std::cout << "value: " << total_value << std::endl;
    std::cout << "weight: " << total_weight << std::endl;

    return 0;
}
