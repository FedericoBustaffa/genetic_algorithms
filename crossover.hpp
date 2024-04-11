#ifndef CROSSOVER_HPP
#define CROSSOVER_HPP

#include <random>
#include <vector>

template <typename genome_type>
std::vector<genome_type> one_point_crossover(const std::vector<genome_type>& p1,
                                             const std::vector<genome_type>& p2,
                                             size_t crossover_point)
{
    std::vector<genome_type> children;
    for (size_t i = 0; i < crossover_point; ++i)
        children.push_back(p1[i]);

    for (size_t i = crossover_point; i < p2.size(); ++i)
        children.push_back(p2[i]);

    return children;
}

template <typename genome_type>
std::vector<std::vector<genome_type>> one_point(
    const std::vector<std::vector<genome_type>>& population, const std::vector<size_t>& parents,
    size_t genome_len, std::default_random_engine& engine)
{
    std::uniform_int_distribution<size_t> parents_dist(0, parents.size() - 1);
    std::uniform_int_distribution<size_t> genome_dist(1, genome_len - 1);

    std::vector<std::vector<genome_type>> children;
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
        children.push_back(one_point_crossover<genome_type>(population[father], population[mother],
                                                            crossover_point));
        children.push_back(one_point_crossover<genome_type>(population[mother], population[father],
                                                            crossover_point));
    }

    return children;
}

#endif  // !CROSSOVER_HPP
