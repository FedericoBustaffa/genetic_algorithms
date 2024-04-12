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
    std::vector<individual<int, int64_t>> population =
        generate_population<int, int64_t>(population_size, num_of_items, {0, 1}, engine);

    for (size_t i = 0; i < population_size; ++i)
    {
        population[i].set_fitness(fitness(population[i].get_genome(), items, capacity));
        for (size_t j = 0; j < num_of_items; ++j)
            std::cout << population[i][j] << std::flush;
        std::cout << ": " << population[i].get_fitness() << std::endl;
    }

    size_t generations = std::stoul(argv[3]);
    std::vector<size_t> parents;
    std::vector<individual<int, int64_t>> children;
    for (size_t g = 0; g < generations; ++g)
    {
        // selection
        parents = tournament<int, int64_t>(population, engine);

        // crossover
        children = one_point<int, int64_t>(population, parents, num_of_items, engine);

        // mutation
        stochastic_mutation<int, int64_t>(children, {0, 1}, num_of_items, 0.01, engine);

        // compute children fitness
        for (size_t i = 0; i < population_size; ++i)
            children[i].set_fitness(fitness(children[i].get_genome(), items, capacity));

        // replacement
    }

    return 0;
}
