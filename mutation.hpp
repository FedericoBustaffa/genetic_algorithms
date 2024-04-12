#ifndef MUTATION_HPP
#define MUTATION_HPP

#include <random>
#include <vector>

#include "individual.hpp"

template <typename T1, typename T2>
void stochastic_mutation(std::vector<individual<T1, T2>>& children, const std::vector<T1>& values,
                         size_t genome_length, double mutation_rate,
                         std::default_random_engine& engine)
{
    std::bernoulli_distribution mutation_dist(mutation_rate);
    std::uniform_int_distribution<size_t> values_dist(0, values.size() - 1);

    T1 old_gene;
    for (size_t i = 0; i < children.size(); ++i)
    {
        for (size_t j = 0; j < genome_length; ++j)
        {
            if (mutation_dist(engine))
            {
                old_gene = children[i][j];
                do
                {
                    children[i][j] = values[values_dist(engine)];
                } while (children[i][j] == old_gene);
            }
        }
    }
}

#endif  // !MUTATION_HPP
