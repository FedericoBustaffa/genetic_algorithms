import random
import sys

import genetic


class item:
    def __init__(self, value: int, weight: int):
        self.value = value
        self.weight = weight


def greedy(items: list[item], capacity: float):
    # sorting
    items = sorted(items, key=lambda x: x.value / x.weight, reverse=True)

    weight = 0
    value = 0
    for i in items:
        if weight + i.weight <= capacity:
            weight += i.weight
            value += i.value

    return value, weight


def fitness(genome, items, capacity):
    value = 0
    weight = 0
    for i in range(len(genome)):
        value += genome[i] * items[i].value
        weight += genome[i] * items[i].weight

    if weight <= capacity:
        return value
    else:
        return -weight


if __name__ == "__main__":
    if len(sys.argv) != 5:
        print(
            "USAGE: py test.py <n-items> <population-size> <generations> <mutation-rate>"
        )
        exit(-1)

    total_value = 0
    total_weight = 0
    num_of_items = int(sys.argv[1])

    items = []
    for i in range(num_of_items):
        items.append(item(random.randint(1, 100), random.randint(1, 100)))
        total_value += items[i].value
        total_weight += items[i].weight

    capacity = total_weight * 0.75

    value, weight = greedy(items, capacity)
    print("GREEDY")
    print(f"value: {value}")
    print(f"weight: {weight}")

    population_size = int(sys.argv[2])
    generations = int(sys.argv[3])
    mutation_rate = float(sys.argv[4])

    knapsack = genetic.ga(
        population_size,
        num_of_items,
        [0, 1],
        generations,
        genetic.problem_type.maximization,
    )

    knapsack.generate_population()
    knapsack.evaluate_population(fitness, items, capacity)

    best = knapsack.get_best_individual()
    value = 0
    weight = 0
    for i in range(num_of_items):
        value += best.get_genome()[i] * items[i].value
        weight += best.get_genome()[i] * items[i].weight

    print("GENETIC FIRST BEST SOLUTION")
    print(f"value: {value}")
    print(f"weight: {weight}")

    current_best = genetic.individual(best)
    for i in range(generations):
        knapsack.tournament()
        knapsack.random_crossover()
        knapsack.random_mutation(mutation_rate)
        knapsack.evaluate_offsprings(fitness, items, capacity)
        knapsack.replace()
        knapsack.evaluate_population(fitness, items, capacity)
        current_best = knapsack.get_best_individual()
        if current_best > best:
            best = current_best

    value = 0
    weight = 0
    for i in range(num_of_items):
        value += best.get_genome()[i] * items[i].value
        weight += best.get_genome()[i] * items[i].weight

    print("GENETIC BEST SOLUTION")
    print(f"value: {value}")
    print(f"weight: {weight}")
