#ifndef SELECTION_HPP
#define SELECTION_HPP

#include <algorithm>
#include <cstddef>
#include <random>

#include "genetic.hpp"

template <typename T1, typename T2>
size_t ga<T1, T2>::tournament_clash()
{
    std::uniform_int_distribution<size_t> population_dist(0, population_size - 1);
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
    for (size_t i = 0; i < population_size / 2; ++i)
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


// ************ FIX ************
template <typename T1, typename T2>
void ga<T1, T2>::roulette()
{
    parents.clear();

    T2 fitness_sum = 0;
    for (size_t i = 0; i < population_size; ++i)
        fitness_sum += population[i].get_fitness();

    std::vector<T2> probabilities;
    for (size_t i = 0; i < population_size; ++i)
        probabilities.push_back(static_cast<double>(population[i].get_fitness()) / fitness_sum);

    std::discrete_distribution<size_t> dist(probabilities.begin(), probabilities.end());
    size_t p;
    int tries = 0;
    for (size_t i = 0; i < population_size / 2; ++i)
    {
        p = population[dist(engine)];
        tries = 0;
        while (std::find(parents.begin(), parents.end(), p) != parents.end() && tries < 20)
        {
            p = population[dist(engine)];
            tries++;
        }
        parents.push_back(p);
    }
}

#endif  // !SELECTION_HPP
