#ifndef SELECTION_HPP
#define SELECTION_HPP

#include <algorithm>
#include <cstddef>

#include "genetic.hpp"

template <typename T1, typename T2>
size_t ga<T1, T2>::tournament_clash()
{
    size_t p1 = population_dist(engine);
    size_t p2 = population_dist(engine);
    int tries = 0;
    while (population[p1] == population[p2] && tries < 20)
    {
        p2 = population_dist(engine);
        tries++;
    }

    return population[p1].get_fitness() > population[p2].get_fitness() ? p1 : p2;
}

template <typename T1, typename T2>
void ga<T1, T2>::tournament()
{
    parents.clear();
    size_t p;
    int tries = 0;
    for (size_t i = 0; i < population.size() / 2; ++i)
    {
        p = tournament_clash();
        tries = 0;
        while (std::find(parents.begin(), parents.end(), p) != parents.end() && tries < 20)
        {
            p = tournament_clash();
            tries++;
        }
        parents.push_back(p);
    }
}

template <typename T1, typename T2>
void ga<T1, T2>::roulette()
{
    parents.clear();
}

#endif  // !SELECTION_HPP
