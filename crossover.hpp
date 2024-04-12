#ifndef CROSSOVER_HPP
#define CROSSOVER_HPP

#include <random>
#include <vector>

#include "genetic.hpp"
#include "individual.hpp"

template <typename T1, typename T2>
individual<T1, T2> ga<T1, T2>::one_point_crossover(const individual<T1, T2>& p1,
                                                   const individual<T1, T2>& p2,
                                                   size_t crossover_point)
{
    std::vector<T1> genome;
    for (size_t i = 0; i < crossover_point; ++i)
        genome.push_back(p1[i]);

    for (size_t i = crossover_point; i < p2.get_genome().size(); ++i)
        genome.push_back(p2[i]);

    return individual<T1, T2>(genome);
}

template <typename T1, typename T2>
void ga<T1, T2>::one_point()
{
    offsprings.clear();

    size_t father;
    size_t mother;
    size_t crossover_point;
    while (offsprings.size() != population.size())
    {
        father = parents[parents_dist(engine)];
        do
        {
            mother = parents[parents_dist(engine)];
        } while (father == mother);

        crossover_point = genome_values_dist(engine);
        offsprings.push_back(one_point_crossover(
            population[father].get_genome(), population[mother].get_genome(), crossover_point));
        offsprings.push_back(one_point_crossover(
            population[mother].get_genome(), population[father].get_genome(), crossover_point));
    }
}

#endif  // !CROSSOVER_HPP
