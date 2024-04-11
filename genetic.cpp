#include <cstddef>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <ostream>
#include <random>
#include <string>

#include "crossover.hpp"
#include "individual.hpp"
#include "item.hpp"
#include "mutation.hpp"
#include "selection.hpp"
#include "spawn.hpp"

int64_t fitness(const std::vector<bool> &genome, const std::vector<item> &items, size_t capacity)
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
    if (argc != 4)
    {
        std::cerr << "USAGE: ./genetic.x <n-items> <population-size> <generations>" << std::endl;
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

    // generate random initial population
    size_t population_size = std::stoul(argv[2]);
    std::vector<individual<bool, int64_t>> population =
        generate_population<bool>(population_size, num_of_items, {true, false}, engine);

    std::cout << "\nfitness values" << std::endl;
    std::vector<int64_t> fitness_values;
    for (size_t i = 0; i < population_size; ++i)
    {
        fitness_values.push_back(fitness(population[i], items, capacity));
        for (size_t j = 0; j < num_of_items; ++j)
            std::cout << population[i][j] << std::flush;
        std::cout << ": " << fitness_values[i] << std::endl;
    }

    size_t generations = std::stoul(argv[3]);
    std::vector<size_t> parents;
    std::vector<std::vector<bool>> children;
    std::vector<int64_t> children_fitness(population_size, 0);
    for (size_t g = 0; g < generations; ++g)
    {
        // selection
        parents = tournament<bool, int64_t>(population, fitness_values, engine);

        // crossover
        children = one_point<bool>(population, parents, num_of_items, engine);

        // mutation
        stochastic_mutation<bool>(children, {false, true}, num_of_items, 0.01, engine);

        // compute children fitness
        for (size_t i = 0; i < population_size; ++i)
            children_fitness[i] = fitness(children[i], items, capacity);

        // replacement
    }

    return 0;
}
