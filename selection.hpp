#ifndef SELECTION_HPP
#define SELECTION_HPP

// #include <algorithm>
// #include <cstddef>
// #include <random>
// #include <vector>
//
// #include "genetic.hpp"
// #include "individual.hpp"
//
// template <typename T1, typename T2>
// size_t ga<T1, T2>::tournament_clash()
// {
//     size_t p1 = dist(engine);
//     size_t p2 = dist(engine);
//     while (population[p1] == population[p2])
//         p2 = dist(engine);
//
//     return population[p1].get_fitness() > population[p2].get_fitness() ? p1 : p2;
// }
//
// template <typename T1, typename T2>
// void ga<T1, T2>::tournament()
// {
//     std::vector<size_t> parents;
//     size_t p;
//     std::uniform_int_distribution<size_t> dist(0, population.size() - 1);
//     for (size_t i = 0; i < population.size() / 2; ++i)
//     {
//         p = clash(population, engine, dist);
//         while (std::find(parents.begin(), parents.end(), p) != parents.end())
//             p = clash(population, engine, dist);
//         parents.push_back(p);
//     }
// }

#endif  // !SELECTION_HPP
