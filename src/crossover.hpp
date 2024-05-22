#ifndef CROSSOVER_HPP
#define CROSSOVER_HPP

#include <cstddef>
#include <cstdlib>
#include <random>
#include <vector>

#include "genetic.hpp"
#include "individual.hpp"

template <typename T1, typename T2>
individual<T1, T2> ga<T1, T2>::one_point(const individual<T1, T2>& p1,
                                         const individual<T1, T2>& p2, size_t crossover_point)
{
    std::vector<T1> genome;
    for (size_t i = 0; i < crossover_point; ++i)
        genome.push_back(p1[i]);

    for (size_t i = crossover_point; i < p2.get_genome().size(); ++i)
        genome.push_back(p2[i]);

    return individual<T1, T2>(genome);
}

template <typename T1, typename T2>
void ga<T1, T2>::one_point_crossover()
{
    offsprings.clear();

    std::uniform_int_distribution<size_t> parents_dist(0, population_size / 2 - 1);
    std::uniform_int_distribution<size_t> genome_values_dist(0, genome_values.size() - 1);

    size_t father;
    size_t mother;
    size_t crossover_point;
    std::vector<T1> father_genome;
    std::vector<T1> mother_genome;
    while (offsprings.size() != population_size)
    {
        father = parents[parents_dist(engine)];
        do
        {
            mother = parents[parents_dist(engine)];
        } while (father == mother);

        crossover_point = genome_values_dist(engine);
        father_genome = population[father].get_genome();
        mother_genome = population[mother].get_genome();

        offsprings.push_back(one_point(father_genome, mother_genome, crossover_point));
        offsprings.push_back(one_point(mother_genome, father_genome, crossover_point));
    }
}

template <typename T1, typename T2>
individual<T1, T2> ga<T1, T2>::one_point_v2(const individual<T1, T2>& p1,
                                            const individual<T1, T2>& p2, size_t crossover_point)
{
    std::vector<T1> genome;
    std::vector<T1> mother_genome = p2.get_genome();
    for (size_t i = 0; i < crossover_point; ++i)
    {
        genome.push_back(p1[i]);
        std::remove(mother_genome.begin(), mother_genome.end(), p1[i]);
    }

    for (size_t i = 0; i < p2.get_genome().size() - crossover_point; ++i)
        genome.push_back(mother_genome[i]);

    return individual<T1, T2>(genome);
}

template <typename T1, typename T2>
void ga<T1, T2>::one_point_crossover_v2()
{
    offsprings.clear();

    std::uniform_int_distribution<size_t> parents_dist(0, population_size / 2 - 1);
    std::uniform_int_distribution<size_t> genome_values_dist(0, genome_values.size() - 1);

    size_t father;
    size_t mother;
    size_t crossover_point;
    std::vector<T1> father_genome;
    std::vector<T1> mother_genome;
    while (offsprings.size() != population_size)
    {
        father = parents[parents_dist(engine)];
        do
        {
            mother = parents[parents_dist(engine)];
        } while (father == mother);

        crossover_point = genome_values_dist(engine);
        father_genome = population[father].get_genome();
        mother_genome = population[mother].get_genome();

        offsprings.push_back(one_point_v2(father_genome, mother_genome, crossover_point));
        offsprings.push_back(one_point_v2(mother_genome, father_genome, crossover_point));
    }
}

template <typename T1, typename T2>
void ga<T1, T2>::random_crossover()
{
    offsprings.clear();

    std::uniform_int_distribution<size_t> parents_dist(0, population_size / 2 - 1);

    size_t father;
    size_t mother;
    std::vector<T1> father_genome;
    std::vector<T1> mother_genome;
    std::vector<T1> offspring_genome(genome_length);
    std::bernoulli_distribution dice(0.5);
    while (offsprings.size() != population_size)
    {
        father = parents[parents_dist(engine)];
        do
        {
            mother = parents[parents_dist(engine)];
        } while (father == mother);

        father_genome = population[father].get_genome();
        mother_genome = population[mother].get_genome();

        for (size_t i = 0; i < genome_length; ++i)
        {
            if (dice(engine))
                offspring_genome[i] = father_genome[i];
            else
                offspring_genome[i] = mother_genome[i];
        }
        offsprings.push_back(offspring_genome);
    }
}

#endif  // !CROSSOVER_HPP
