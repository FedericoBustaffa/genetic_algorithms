#ifndef SELECTION_HPP
#define SELECTION_HPP

#include <algorithm>
#include <cstddef>
#include <random>
#include <vector>

#include "individual.hpp"

template <typename T1, typename T2>
size_t clash(const std::vector<individual<T1, T2>>& population, std::default_random_engine& engine,
             std::uniform_int_distribution<size_t>& dist)
{
    size_t p1 = dist(engine);
    size_t p2 = dist(engine);
    while (population[p1] == population[p2])
        p2 = dist(engine);

    return population[p1].get_fitness() > population[p2].get_fitness() ? p1 : p2;
}

template <typename T1, typename T2>
std::vector<size_t> tournament(const std::vector<individual<T1, T2>>& population,
                               std::default_random_engine& engine)
{
    std::vector<size_t> parents;
    size_t p;
    std::uniform_int_distribution<size_t> dist(0, population.size() - 1);
    for (size_t i = 0; i < population.size() / 2; ++i)
    {
        p = clash<T1, T2>(population, engine, dist);
        while (std::find(parents.begin(), parents.end(), p) != parents.end())
            p = clash<T1, T2>(population, engine, dist);
        parents.push_back(p);
    }

    return parents;
}

#endif  // !SELECTION_HPP
