import math
import random
import sys

import genetic


class town:
    def __init__(self, x: float, y: float):
        self.x = x
        self.y = y


def fitness(genome, towns):
    total_distance = 0
    for i in range(len(towns) - 1):
        x = towns[genome[i]].x - towns[genome[i + 1]].x
        y = towns[genome[i]].y - towns[genome[i + 1]].y

        total_distance += math.sqrt(math.pow(x, 2) + math.pow(y, 2))

    return total_distance / (len(towns) - 1)


if __name__ == "__main__":
    if len(sys.argv) != 5:
        print(
            "USAGE: py tsp.py <n-towns> <population-size> <generations> <mutation-rate>"
        )
        exit(-1)

    num_of_towns = int(sys.argv[1])
    towns = []
    genome_values = []
    for i in range(num_of_towns):
        t = town(random.uniform(50, 100), random.uniform(50, 100))
        while t in towns:
            t = town(random.uniform(50, 100), random.uniform(50, 100))
        towns.append(t)
        genome_values.append(i)

    population_size = int(sys.argv[2])
    generations = int(sys.argv[3])
    mutation_rate = float(sys.argv[4])

    tsp = genetic.ga(
        population_size,
        num_of_towns,
        genome_values,
        generations,
        genetic.problem_type.minimization,
    )

    tsp.shuffle_generate_population()
    tsp.evaluate_population(fitness, towns)

    best_individual = tsp.get_best_individual()
    print(f"best distance: {best_individual.get_fitness()}")

    current_best = genetic.individual(best_individual)
    for g in range(generations):
        tsp.roulette()
        tsp.one_point_crossover_v2()
        tsp.rotate_mutation(mutation_rate)
        tsp.evaluate_offsprings(fitness, towns)
        tsp.replace()
        tsp.evaluate_population(fitness, towns)
        current_best = tsp.get_best_individual()
        if current_best > best_individual:
            best_individual = current_best

    print(f"best distance: {best_individual.get_fitness()}")
