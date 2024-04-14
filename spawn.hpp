#ifndef SPAWN_HPP
#define SPAWN_HPP

#include <algorithm>
#include <cstddef>
#include <random>
#include <vector>

#include "genetic.hpp"
#include "individual.hpp"

template <typename T1, typename T2>
individual<T1, T2> ga<T1, T2>::generate_genome(bool with_repetitions)
{
    std::uniform_int_distribution<size_t> genome_values_dist(0, genome_values.size() - 1);
    std::vector<T1> genome;
    T1 new_gene;
    for (size_t i = 0; i < genome_length; ++i)
    {
        new_gene = genome_values[genome_values_dist(engine)];
        if (!with_repetitions)
        {
            while (std::find(genome.begin(), genome.end(), new_gene) != genome.end())
                new_gene = genome_values[genome_values_dist(engine)];
        }
        genome.push_back(new_gene);
    }

    return individual<T1, T2>(genome);
}

template <typename T1, typename T2>
void ga<T1, T2>::generate_population(bool with_repetitions)
{
    individual<T1, T2> new_individual;
    for (size_t i = 0; i < population_size; ++i)
    {
        new_individual = generate_genome(with_repetitions);
        while (std::find(population.begin(), population.end(), new_individual) != population.end())
            new_individual = generate_genome(with_repetitions);

        population.push_back(new_individual);
    }
}

#endif  // !SPAWN_HPP
