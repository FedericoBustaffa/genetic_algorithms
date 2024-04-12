#ifndef REPLACEMENT_HPP
#define REPLACEMENT_HPP

#include <algorithm>
#include <vector>

#include "individual.hpp"

template <typename T1, typename T2>
std::vector<individual<T1, T2>> replacement(std::vector<individual<T1, T2>> &population,
                                            std::vector<individual<T1, T2>> &children)
{
    std::sort(population.rbegin(), population.rend());
    std::sort(children.rbegin(), children.rend());

    std::vector<individual<T1, T2>> best_population;
    size_t population_idx = 0;
    size_t children_idx = 0;
    for (size_t i = 0; i < population.size(); ++i)
    {
        if (population[population_idx] > children[children_idx])
        {
            best_population.push_back(population[population_idx]);
            population_idx++;
        }
        else
        {
            best_population.push_back(children[children_idx]);
            children_idx++;
        }
    }

    return best_population;
}

#endif  // !REPLACEMENT_HPP
