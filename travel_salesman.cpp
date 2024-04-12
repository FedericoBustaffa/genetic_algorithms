#include <cstddef>
#include <cstdint>
#include <iostream>

#include "genetic_algorithms.hpp"

int main(int argc, const char** argv)
{
    if (argc != 5)
    {
        std::cerr << "USAGE: ./tsp.x <n-items> <population-size> <generations> <mutation-rate>"
                  << std::endl;
        return 1;
    }

    // generate random items
    std::default_random_engine engine(std::time(nullptr));
    std::uniform_int_distribution<int64_t> dist(1, 50);

    size_t num_of_towns = std::stoul(argv[1]);
    // std::vector<town> towns;

    std::cout << "************ GENETIC ****************" << std::endl;
    size_t population_size = std::stoul(argv[2]);
    size_t generations = std::stoul(argv[3]);
    double mutation_rate = std::stod(argv[4]);

    ga<int64_t, double> genetic_tsp(population_size, num_of_towns, {}, generations);
    genetic_tsp.generate_population();
    // genetic_tsp.evaluate_population(fitness, )

    auto best_individual = genetic_tsp.get_best_individual();

    for (size_t g = 0; g < generations; ++g)
    {
        genetic_tsp.tournament();
        genetic_tsp.one_point_crossover();
        genetic_tsp.random_mutate(mutation_rate);
        // genetic_tsp.evaluate_offsprings(fitness, items, capacity);
        genetic_tsp.replace();
        // genetic_tsp.evaluate_population(fitness, items, capacity);
    }
    best_individual = genetic_tsp.get_best_individual();

    return 0;
}
