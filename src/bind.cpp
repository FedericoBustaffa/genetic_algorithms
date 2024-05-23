#include <pybind11/attr.h>
#include <pybind11/cast.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "genetic.hpp"

namespace py = pybind11;

void modify(int& a) { a = 1; }

void sum_one(py::array_t<int>& l)
{
    for (size_t i = 0; i < l.size(); ++i)
        l[i] = l[i] + 1;
}

PYBIND11_MODULE(genetic, m)
{
    m.def("modify", &modify, "modify a number into 1");

    m.def("sum_one", &sum_one, "sum one to all numbers");

    py::enum_<problem_type>(m, "problem_type")
        .value("minimization", problem_type::minimization)
        .value("maximization", problem_type::maximization)
        .export_values();

    py::class_<ga<int64_t, int64_t>>(m, "ga")
        .def(py::init<size_t, size_t, const std::vector<int64_t>&, size_t, problem_type>())
        .def("get_population_size", &ga<int64_t, int64_t>::get_population_size);
}
