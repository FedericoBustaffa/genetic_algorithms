#ifndef SPAWN_HPP
#define SPAWN_HPP

#include <algorithm>
#include <cstddef>
#include <random>
#include <vector>

#include "genetic.hpp"
#include "individual.hpp"

template <typename T1, typename T2>
individual<T1, T2> ga<T1, T2>::generate_genome()
{
    std::vector<T1> genome;
    for (size_t i = 0; i < genome_length; ++i)
        genome.push_back(genome_values[genome_values_dist(engine)]);

    return individual<T1, T2>(genome);
}

template <typename T1, typename T2>
void ga<T1, T2>::generate_population()
{
    individual<T1, T2> new_individual;
    for (size_t i = 0; i < population_size; ++i)
    {
        new_individual = generate_genome();
        while (std::find(population.begin(), population.end(), new_individual) != population.end())
            new_individual = generate_genome();

        population.push_back(new_individual);
    }
}

#endif  // !SPAWN_HPP
