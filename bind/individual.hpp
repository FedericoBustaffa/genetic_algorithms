#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

#include <cstddef>
#include <iostream>
#include <iterator>
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

    void operator=(const individual& other)
    {
        genome = other.genome;
        fitness = other.fitness;
    }

    genome_type& set(const size_t i) { return genome[i]; }

    const genome_type get(const size_t i) const { return genome[i]; }

    const genome_type operator[](const size_t i) const { return genome[i]; }

    genome_type& operator[](const size_t i) { return genome[i]; }

    bool operator==(const individual& other) const { return genome == other.genome; }

    bool operator<(const individual& other) const { return fitness < other.fitness; }

    bool operator<=(const individual& other) const { return fitness <= other.fitness; }

    bool operator>(const individual& other) const { return fitness > other.fitness; }

    bool operator>=(const individual& other) const { return fitness >= other.fitness; }

    fitness_type get_fitness() const { return fitness; }

    void set_fitness(fitness_type value) { fitness = value; }

    const std::vector<genome_type>& get_genome() const { return genome; }

    void set_genome(const std::vector<genome_type>& new_genome) { genome = new_genome; }

  private:
    std::vector<genome_type> genome;
    fitness_type fitness;
};

#endif  // !INDIVIDUAL_HPP
