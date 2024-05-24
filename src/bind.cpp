#include <pybind11/functional.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/stl.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "crossover.hpp"
#include "evaluation.hpp"
#include "individual.hpp"
#include "mutation.hpp"
#include "replacement.hpp"
#include "selection.hpp"
#include "spawn.hpp"

namespace py = pybind11;

PYBIND11_MODULE(genetic, m)
{
    m.doc() = "Genetic algorithm module";

    py::class_<individual<int64_t, int64_t>>(m, "individual")
        .def(py::init<const std::vector<int64_t> &>())
        .def(py::init<const individual<int64_t, int64_t> &>())
        .def(py::self == py::self)
        .def(py::self < py::self)
        .def(py::self <= py::self)
        .def(py::self > py::self)
        .def(py::self >= py::self)
        .def("get_fitness", &individual<int64_t, int64_t>::get_fitness)
        .def("set_fitness", &individual<int64_t, int64_t>::set_fitness)
        .def("get_genome", &individual<int64_t, int64_t>::get_genome)
        .def("set_genome", &individual<int64_t, int64_t>::set_genome);

    py::class_<individual<int64_t, double>>(m, "individual")
        .def(py::init<const std::vector<int64_t> &>())
        .def(py::init<const individual<int64_t, double> &>())
        .def(py::self == py::self)
        .def(py::self < py::self)
        .def(py::self <= py::self)
        .def(py::self > py::self)
        .def(py::self >= py::self)
        .def("get_fitness", &individual<int64_t, double>::get_fitness)
        .def("set_fitness", &individual<int64_t, double>::set_fitness)
        .def("get_genome", &individual<int64_t, double>::get_genome)
        .def("set_genome", &individual<int64_t, double>::set_genome);

    py::enum_<problem_type>(m, "problem_type")
        .value("minimization", problem_type::minimization)
        .value("maximization", problem_type::maximization)
        .export_values();

    py::class_<ga<int64_t, int64_t>>(m, "ga")
        .def(py::init<size_t, size_t, const std::vector<int64_t> &, size_t, problem_type>())

        .def("get_population", &ga<int64_t, int64_t>::get_population)
        .def("get_population_size", &ga<int64_t, int64_t>::get_population_size)
        .def("get_genome_length", &ga<int64_t, int64_t>::get_genome_length)
        .def("get_best_individual", &ga<int64_t, int64_t>::get_best_individual)

        .def("generate_population", &ga<int64_t, int64_t>::generate_population)
        .def("shuffle_generate_population", &ga<int64_t, int64_t>::shuffle_generate_population)

        .def("evaluate_population", &ga<int64_t, int64_t>::evaluate_population_py<py::int_>)
        .def("evaluate_offsprings", &ga<int64_t, int64_t>::evaluate_offsprings_py<py::int_>)

        .def("tournament", &ga<int64_t, int64_t>::tournament)
        .def("roulette", &ga<int64_t, int64_t>::roulette)

        .def("one_point_crossover", &ga<int64_t, int64_t>::one_point_crossover)
        .def("one_point_crossover_v2", &ga<int64_t, int64_t>::one_point_crossover_v2)
        .def("random_crossover", &ga<int64_t, int64_t>::random_crossover)

        .def("random_mutation", &ga<int64_t, int64_t>::random_mutation)
        .def("swap_mutation", &ga<int64_t, int64_t>::swap_mutation)
        .def("rotate_mutation", &ga<int64_t, int64_t>::rotate_mutation)

        .def("replace", &ga<int64_t, int64_t>::replace);

    py::class_<ga<int64_t, double>>(m, "ga")
        .def(py::init<size_t, size_t, const std::vector<int64_t> &, size_t, problem_type>())

        .def("get_population", &ga<int64_t, double>::get_population)
        .def("get_population_size", &ga<int64_t, double>::get_population_size)
        .def("get_genome_length", &ga<int64_t, double>::get_genome_length)
        .def("get_best_individual", &ga<int64_t, double>::get_best_individual)

        .def("generate_population", &ga<int64_t, double>::generate_population)
        .def("shuffle_generate_population", &ga<int64_t, double>::shuffle_generate_population)

        .def("evaluate_population", &ga<int64_t, double>::evaluate_population_py<py::float_>)
        .def("evaluate_offsprings", &ga<int64_t, double>::evaluate_offsprings_py<py::float_>)

        .def("tournament", &ga<int64_t, double>::tournament)
        .def("roulette", &ga<int64_t, double>::roulette)

        .def("one_point_crossover", &ga<int64_t, double>::one_point_crossover)
        .def("one_point_crossover_v2", &ga<int64_t, double>::one_point_crossover_v2)
        .def("random_crossover", &ga<int64_t, double>::random_crossover)

        .def("random_mutation", &ga<int64_t, double>::random_mutation)
        .def("swap_mutation", &ga<int64_t, double>::swap_mutation)
        .def("rotate_mutation", &ga<int64_t, double>::rotate_mutation)

        .def("replace", &ga<int64_t, double>::replace);
}
