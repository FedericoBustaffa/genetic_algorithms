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

    const genome_type operator[](size_t i) const { return genome[i]; }

    genome_type& operator[](size_t i) { return genome[i]; }

    bool operator==(const individual& other) const
    {
        return genome == other.genome && fitness == other.fitness;
    }

    fitness_type get_fitness() const { return fitness; }

    void set_fitness(fitness_type value) { fitness = value; }

    const std::vector<genome_type>& get_genome() const { return genome; }

  private:
    std::vector<genome_type> genome;
    fitness_type fitness;
};

#endif  // !INDIVIDUAL_HPP
