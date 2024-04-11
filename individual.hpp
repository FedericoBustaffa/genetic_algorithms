#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

#include <cstddef>
#include <vector>

template <typename genome_type, typename fitness_type>
class individual
{
  public:
    individual() : genome({}), fitness(0) {}

    individual(const std::vector<genome_type>& genome) : genome(genome), fitness(0) {}

    individual(const individual& other)
    {
        genome = other.genome;
        fitness = other.fitness;
    }

    genome_type operator[](size_t i) { return genome[i]; }
    fitness_type get_fitness() { return fitness; }

  private:
    std::vector<genome_type> genome;
    fitness_type fitness;
};

#endif  // !INDIVIDUAL_HPP
