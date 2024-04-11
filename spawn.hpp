#ifndef SPAWN_HPP
#define SPAWN_HPP

#include <algorithm>
#include <cstddef>
#include <random>
#include <vector>

#include "individual.hpp"

template <typename T1>
std::vector<T1> generate_genome(size_t genome_length, const std::vector<T1>& values,
                                std::default_random_engine& engine,
                                std::uniform_int_distribution<size_t>& dist)
{
    std::vector<T1> genome;
    for (size_t i = 0; i < genome_length; ++i)
        genome.push_back(values[dist(engine)]);

    return genome;
}

template <typename T1, typename T2>
std::vector<individual<T1, T2>> generate_population(size_t population_size, size_t genome_length,
                                                    const std::vector<T1>& values,
                                                    std::default_random_engine& engine)
{
    std::vector<individual<T1, T2>> population;
    std::uniform_int_distribution<size_t> dist(0, values.size() - 1);
    std::vector<T1> genome;
    for (size_t i = 0; i < population_size; ++i)
    {
        genome = generate_genome<T1>(genome_length, values, engine, dist);
        while (std::find(population.begin(), population.end(), genome) != population.end())
            genome = generate_genome<T1>(genome_length, values, engine, dist);

        population.push_back(genome);
    }

    return population;
}

#endif  // !SPAWN_HPP
