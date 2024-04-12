#ifndef CROSSOVER_HPP
#define CROSSOVER_HPP

#include <random>
#include <vector>

#include "individual.hpp"

template <typename T1, typename T2>
individual<T1, T2> one_point_crossover(const individual<T1, T2>& p1, const individual<T1, T2>& p2,
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
std::vector<individual<T1, T2>> one_point(const std::vector<individual<T1, T2>>& population,
                                          const std::vector<size_t>& parents, size_t genome_len,
                                          std::default_random_engine& engine)
{
    std::uniform_int_distribution<size_t> parents_dist(0, parents.size() - 1);
    std::uniform_int_distribution<size_t> genome_dist(1, genome_len - 1);

    std::vector<individual<T1, T2>> children;
    size_t father;
    size_t mother;
    size_t crossover_point;
    while (children.size() != population.size())
    {
        father = parents[parents_dist(engine)];
        do
        {
            mother = parents[parents_dist(engine)];
        } while (father == mother);

        crossover_point = genome_dist(engine);
        children.push_back(one_point_crossover<T1, T2>(
            population[father].get_genome(), population[mother].get_genome(), crossover_point));
        children.push_back(one_point_crossover<T1, T2>(
            population[mother].get_genome(), population[father].get_genome(), crossover_point));
    }

    return children;
}

#endif  // !CROSSOVER_HPP
