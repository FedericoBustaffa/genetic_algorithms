#ifndef GENETIC_HPP
#define GENETIC_HPP

#include <ctime>
#include <random>
#include <vector>

#include "individual.hpp"

template <typename T1, typename T2>
class ga
{
  public:
    ga(size_t population_size, size_t genome_length, const std::vector<T1>& genome_values,
       size_t generations, double mutation_rate)
        : population_size(population_size),
          genome_length(genome_length),
          genome_values(genome_values),
          generations(generations),
          mutation_rate(mutation_rate),
          engine(std::time(nullptr)),
          genome_values_dist(0, genome_values.size() - 1)
    {
        population.reserve(population_size);
        offsprings.reserve(population_size);
    }

    // get/set methods
    const std::vector<individual<T1, T2>>& get_population() const { return population; }

    size_t get_population_size() const { return population_size; }

    // genetic methods
    // population_generation
    void generate_population();

    // evaluate the population with the given fitness function
    template <typename Callable, typename... Args>
    void evaluate_population(Callable fitness, Args... args)
    {
        for (size_t i = 0; i < population_size; ++i)
            population[i].set_fitness(fitness(population[i].get_genome(), args...));
    }

    // Selection systems
    // void tournament();

  private:
    // support methods

    // generate a random genome
    individual<T1, T2> generate_genome();

    // FIX
    // size_t tournament_clash();

  private:
    // paremeters
    size_t population_size;
    size_t genome_length;
    std::vector<T1> genome_values;
    size_t generations;
    double mutation_rate;

    // individuals
    std::vector<individual<T1, T2>> population;
    std::vector<individual<T1, T2>> offsprings;
    individual<T1, T2> best_individual;

    // random engine
    std::default_random_engine engine;
    std::uniform_int_distribution<size_t> genome_values_dist;
};

#endif  // !GENETIC_HPP
