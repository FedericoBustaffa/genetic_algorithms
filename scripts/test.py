import random
import sys

import genetic


class item:
    def __init__(self, value: int, weight: int):
        self.value = value
        self.weight = weight


def fitness(genome: list[int], items: list[item], capacity: int):
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

    for i in knapsack.get_population():
        print(i.get_genome())
