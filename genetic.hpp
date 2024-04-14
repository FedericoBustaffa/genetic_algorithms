#ifndef GENETIC_HPP
#define GENETIC_HPP

#include <algorithm>
#include <random>
#include <vector>

#include "individual.hpp"

enum class problem_type
{
    minimization,
    maximization
};

template <typename T1, typename T2>
class ga
{
  public:
    ga(size_t population_size, size_t genome_length, const std::vector<T1>& genome_values,
       size_t generations, problem_type type)
        : population_size(population_size),
          genome_length(genome_length),
          genome_values(genome_values),
          generations(generations),
          type(type),
          engine(rd())
    {
        population.reserve(population_size);
        parents.reserve(population_size / 2);
        offsprings.reserve(population_size);
    }

    // get methods
    const std::vector<individual<T1, T2>>& get_population() const { return population; }

    size_t get_population_size() const { return population_size; }

    size_t get_genome_length() const { return genome_length; }

    const individual<T1, T2>& get_best_individual()
    {
        if (type == problem_type::minimization)
            std::sort(population.begin(), population.end());
        else
            std::sort(population.rbegin(), population.rend());

        return population[0];
    }

    // genetic methods
    // population_generation
    void generate_population(bool with_repetitions);

    // evaluate the population with the given fitness function
    template <typename Callable, typename... Args>
    void evaluate_population(Callable fitness, Args... args);

    template <typename Callable, typename... Args>
    void evaluate_offsprings(Callable fitness, Args... args);

    // Selection systems
    void tournament();

    void roulette();

    // crossover operators
    // split the father's and mother's genomes in one random point
    void one_point_crossover();

    //
    void random_crossover();

    // mutation operators
    void random_mutate(double mutation_rate);

    // replacemente policies
    void replace();

  private:
    // support methods

    // generate a random genome
    individual<T1, T2> generate_genome(bool with_repetitions);

    // choose two random individuals for reproduction
    // higher fitness wins
    size_t tournament_clash();

    // crossover
    individual<T1, T2> one_point(const individual<T1, T2>& a, const individual<T1, T2>& b,
                                 size_t crossover_point);

  private:
    // paremeters
    size_t population_size;
    size_t genome_length;
    std::vector<T1> genome_values;
    size_t generations;
    problem_type type;

    // individuals
    std::vector<individual<T1, T2>> population;
    std::vector<size_t> parents;
    std::vector<individual<T1, T2>> offsprings;

    // random engine
    std::random_device rd;
    std::mt19937 engine;
};

#endif  // !GENETIC_HPP
