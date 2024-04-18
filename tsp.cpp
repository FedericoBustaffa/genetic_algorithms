#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>

#include "genetic_algorithms.hpp"

struct town
{
    town(double x, double y) : x(x), y(y) {}

    bool operator==(const town& other) { return x == other.x && y == other.y; }

    double x;
    double y;
};

double fitness(const std::vector<int64_t> genome, const std::vector<town>& towns)
{
    double total_distance = 0;
    double x;
    double y;
    for (size_t i = 0; i < genome.size() - 1; ++i)
    {
        x = towns[genome[i]].x - towns[genome[i + 1]].x;
        y = towns[genome[i]].y - towns[genome[i + 1]].y;

        total_distance += std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    }

    return total_distance;
}

int main(int argc, const char** argv)
{
    if (argc != 5)
    {
        std::cerr << "USAGE: ./tsp.x <n-towns> <population-size> <generations> <mutation-rate>"
                  << std::endl;
        return 1;
    }

    // generate random items
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_real_distribution<double> dist(50, 1000);

    size_t num_of_towns = std::stoul(argv[1]);
    std::vector<town> towns;
    std::vector<int64_t> genome_values;
    for (size_t i = 0; i < num_of_towns; ++i)
    {
        town new_town(dist(engine), dist(engine));

        while (std::find(towns.begin(), towns.end(), new_town) != towns.end())
            new_town = {dist(engine), dist(engine)};
        towns.push_back({dist(engine), dist(engine)});
        genome_values.push_back(i);
    }

    std::cout << "************ GENETIC ****************" << std::endl;
    size_t population_size = std::stoul(argv[2]);
    size_t generations = std::stoul(argv[3]);
    double mutation_rate = std::stod(argv[4]);

    ga<int64_t, double> genetic_tsp(population_size, num_of_towns, genome_values, generations,
                                    problem_type::minimization);
    genetic_tsp.shuffle_generate_population();
    genetic_tsp.evaluate_population(fitness, towns);

    auto best_individual = genetic_tsp.get_best_individual();
    std::cout << "best distance: " << best_individual.get_fitness() << std::endl;

    std::ofstream file("towns.csv");
    file << "x,y" << std::endl;
    for (size_t i = 0; i < num_of_towns; ++i)
        file << towns[i].x << "," << towns[i].y << std::endl;

    individual<int64_t, double> current_best;
    std::bernoulli_distribution mutation_dist(0.5);
    for (size_t g = 0; g < generations; ++g)
    {
        genetic_tsp.roulette();

        genetic_tsp.one_point_crossover_v2();

        if (mutation_dist(engine))
            genetic_tsp.rotate_mutation(mutation_rate);
        else
            genetic_tsp.swap_mutation(mutation_rate);

        genetic_tsp.evaluate_offsprings(fitness, towns);

        genetic_tsp.replace();

        genetic_tsp.evaluate_population(fitness, towns);

        current_best = genetic_tsp.get_best_individual();
        if (current_best > best_individual)
            best_individual = current_best;
    }

    best_individual = genetic_tsp.get_best_individual();
    std::cout << "best distance: " << best_individual.get_fitness() << std::endl;
    std::ofstream solution("solution.txt");
    for (size_t i = 0; i < num_of_towns; ++i)
        solution << best_individual[i] << std::endl;

    return 0;
}
