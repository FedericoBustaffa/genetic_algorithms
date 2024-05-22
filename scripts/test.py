import genetic

pet = genetic.pet("Charlie", 1)
print(pet.get_name())
pet.set_name("Willy")
print(pet.get_name())

print(pet.get())

ga = genetic.ga(10, 10, [0, 1], 30, genetic.problem_type.minimization)
print(ga.get_population_size())
