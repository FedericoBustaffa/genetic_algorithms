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
    void generate_population();

    void shuffle_generate_population();

    // evaluate the population with the given fitness function
    template <typename Callable, typename... Args>
    void evaluate_population(Callable fitness, Args... args);

    // evaluate offsprings with the given fitness function
    template <typename Callable, typename... Args>
    void evaluate_offsprings(Callable fitness, Args... args);

    // Selection systems
    // pick randomly two individuals, the one with higher fitness
    // is chosen to be a parent
    void tournament();

    // pick randomly an individual
    // individuals with higher fitness have more chances to be chosen
    // DOES NOT WORK WITH NEGATIVE FITNESS VALUES
    void roulette();

    // crossover operators
    // split the father's and mother's genomes in one random point
    void one_point_crossover();

    // the offspring takes half of father's genome as it is and
    // then the remaining mother's genes are chosen excluding the
    // genes already passed by father
    void one_point_crossover_v2();

    // every gene has 50% of chance to be ineherited by father or mother
    void random_crossover();

    // mutation operators
    void random_mutation(double mutation_rate);

    // swap two genes
    void swap_mutation(double mutation_rate);

    //
    void rotate_mutation(double mutation_rate);

    // replacemente policies
    void replace();

  private:
    // support methods

    // generate a random genome
    individual<T1, T2> generate_genome();

    // choose two random individuals for reproduction
    // higher fitness wins
    size_t tournament_clash();

    // crossover
    individual<T1, T2> one_point(const individual<T1, T2>& a, const individual<T1, T2>& b,
                                 size_t crossover_point);

    individual<T1, T2> one_point_v2(const individual<T1, T2>& a, const individual<T1, T2>& b,
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
