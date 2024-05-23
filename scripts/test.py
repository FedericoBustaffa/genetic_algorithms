import genetic

a = 2
genetic.modify(a)
print(a)

l = [1, 2, 3]
genetic.sum_one(l)
print(l)

ga = genetic.ga(10, 10, [0, 1], 30, genetic.problem_type.minimization)
print(ga.get_population_size())
