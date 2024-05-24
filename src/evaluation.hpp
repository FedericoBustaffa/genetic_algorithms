#ifndef EVALUATION_HPP
#define EVALUATION_HPP

#include <pybind11/cast.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/stl.h>

#include "genetic.hpp"

namespace py = pybind11;

template <typename T1, typename T2>
template <typename Callable, typename... Args>
void ga<T1, T2>::evaluate_population(Callable fitness, Args... args)
{
    for (size_t i = 0; i < population_size; ++i)
        population[i].set_fitness(fitness(population[i].get_genome(), args...));
}

template <typename T1, typename T2>
template <typename py_type>
void ga<T1, T2>::evaluate_population_py(const py::function& fitness, const py::args& args)
{
    for (size_t i = 0; i < population_size; ++i)
        population[i].set_fitness(
            static_cast<py_type>(fitness(population[i].get_genome(), *args)));
}

template <typename T1, typename T2>
template <typename Callable, typename... Args>
void ga<T1, T2>::evaluate_offsprings(Callable fitness, Args... args)
{
    for (size_t i = 0; i < population_size; ++i)
        offsprings[i].set_fitness(fitness(offsprings[i].get_genome(), args...));
}

template <typename T1, typename T2>
template <typename py_type>
void ga<T1, T2>::evaluate_offsprings_py(const py::function& fitness, const py::args& args)
{
    for (size_t i = 0; i < population_size; ++i)
        offsprings[i].set_fitness(
            static_cast<py_type>(fitness(population[i].get_genome(), *args)));
}

#endif  // !EVALUATION_HPP
