#ifndef MUTATION_HPP
#define MUTATION_HPP

#include <random>
#include <vector>

#include "genetic.hpp"

template <typename T1, typename T2>
void ga<T1, T2>::random_mutation(double mutation_rate)
{
    std::bernoulli_distribution mutation_dist(mutation_rate);
    std::uniform_int_distribution<size_t> genome_values_dist(0, genome_values.size() - 1);

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

template <typename T1, typename T2>
void ga<T1, T2>::swap_mutation(double mutation_rate)
{
    std::bernoulli_distribution mutation_dist(mutation_rate);
    std::uniform_int_distribution<size_t> genome_dist(0, genome_length - 1);

    size_t to_swap_gene;
    for (size_t i = 0; i < population_size; ++i)
    {
        for (size_t j = 0; j < genome_length; ++j)
        {
            if (mutation_dist(engine))
            {
                to_swap_gene = genome_dist(engine);
                while (to_swap_gene == j)
                    to_swap_gene = genome_dist(engine);

                size_t tmp = offsprings[i][j];
                offsprings[i][j] = offsprings[i][to_swap_gene];
                offsprings[i][to_swap_gene] = tmp;
            }
        }
    }
}

template <typename T1, typename T2>
void ga<T1, T2>::rotate_mutation(double mutation_rate)
{
    std::bernoulli_distribution mutation_dist(mutation_rate);

    size_t pivot;
    for (size_t i = 0; i < population_size; ++i)
    {
        for (size_t j = 0; j < genome_length; ++j)
        {
            if (mutation_dist(engine))
            {
                std::vector<T1> genome = offsprings[i].get_genome();
                pivot = (genome_length + j) / 2;
                // implement rotation
            }
        }
    }
}

#endif  // !MUTATION_HPP
