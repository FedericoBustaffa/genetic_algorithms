#ifndef REPLACEMENT_HPP
#define REPLACEMENT_HPP

#include <algorithm>
#include <vector>

#include "genetic.hpp"
#include "individual.hpp"

template <typename T1, typename T2>
void ga<T1, T2>::replace()
{
    std::sort(population.rbegin(), population.rend());
    std::sort(offsprings.rbegin(), offsprings.rend());

    std::vector<individual<T1, T2>> best_population;
    size_t population_idx = 0;
    size_t children_idx = 0;
    for (size_t i = 0; i < population.size(); ++i)
    {
        if (population[population_idx] > offsprings[children_idx])
        {
            best_population.push_back(population[population_idx]);
            population_idx++;
        }
        else
        {
            best_population.push_back(offsprings[children_idx]);
            children_idx++;
        }
    }

    population = best_population;
}

#endif  // !REPLACEMENT_HPP
