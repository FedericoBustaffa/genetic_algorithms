#ifndef REPLACEMENT_HPP
#define REPLACEMENT_HPP

#include <vector>

#include "genetic.hpp"
#include "individual.hpp"

template <typename T1, typename T2>
void ga<T1, T2>::replace()
{
    std::vector<individual<T1, T2>> best_population;
    size_t population_idx = 0;
    size_t children_idx = 0;
    if (type == problem_type::minimization)
    {
        std::sort(population.begin(), population.end());
        for (size_t i = 0; i < population_size; ++i)
        {
            if (population[population_idx] < offsprings[children_idx])
                best_population.push_back(population[population_idx++]);
            else
                best_population.push_back(offsprings[children_idx++]);
        }
    }
    else
    {
        std::sort(population.rbegin(), population.rend());
        for (size_t i = 0; i < population_size; ++i)
        {
            if (population[population_idx] > offsprings[children_idx])
                best_population.push_back(population[population_idx++]);
            else
                best_population.push_back(offsprings[children_idx++]);
        }
    }

    population = best_population;
}

#endif  // !REPLACEMENT_HPP
