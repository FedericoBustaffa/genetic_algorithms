#ifndef MUTATION_HPP
#define MUTATION_HPP

#include <random>
#include <vector>

#include "genetic.hpp"

template <typename T1, typename T2>
void ga<T1, T2>::random_mutate(double mutation_rate)
{
    std::bernoulli_distribution mutation_dist(mutation_rate);

    T1 old_gene;
    for (size_t i = 0; i < offsprings.size(); ++i)
    {
        for (size_t j = 0; j < genome_length; ++j)
        {
            if (mutation_dist(engine))
            {
                old_gene = offsprings[i][j];
                do
                {
                    offsprings[i][j] = genome_values[genome_values_dist(engine)];
                } while (offsprings[i][j] == old_gene);
            }
        }
    }
}

#endif  // !MUTATION_HPP
