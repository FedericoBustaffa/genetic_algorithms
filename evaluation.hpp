#ifndef EVALUATION_HPP
#define EVALUATION_HPP

#include <algorithm>

#include "genetic.hpp"

template <typename T1, typename T2>
template <typename Callable, typename... Args>
void ga<T1, T2>::evaluate_population(Callable fitness, Args... args)
{
    for (size_t i = 0; i < population_size; ++i)
        population[i].set_fitness(fitness(population[i].get_genome(), args...));

    std::sort(population.rbegin(), population.rend());

    if (population[0] > best_individual)
        best_individual = population[0];
}

template <typename T1, typename T2>
template <typename Callable, typename... Args>
void ga<T1, T2>::evaluate_offsprings(Callable fitness, Args... args)
{
    for (size_t i = 0; i < population_size; ++i)
        offsprings[i].set_fitness(fitness(offsprings[i].get_genome(), args...));

    std::sort(offsprings.rbegin(), offsprings.rend());
}

#endif  // !EVALUATION_HPP
