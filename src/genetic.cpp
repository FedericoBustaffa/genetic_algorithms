#include "genetic.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace py = pybind11;

template <typename T>
class pet
{
  public:
    pet(const std::string& name, T value) : name(name), value(value) {}

    void set_name(const std::string& name) { this->name = name; }

    const std::string& get_name() const { return name; }

    T get() const { return value; }

  private:
    std::string name;
    T value;
};

PYBIND11_MODULE(genetic, m)
{
    py::class_<pet<int>>(m, "pet")
        .def(py::init<const std::string&, int>())
        .def("set_name", &pet<int>::set_name)
        .def("get_name", &pet<int>::get_name)
        .def("get", &pet<int>::get);

    py::enum_<problem_type>(m, "problem_type")
        .value("minimization", problem_type::minimization)
        .value("maximization", problem_type::maximization)
        .export_values();

    py::class_<ga<int64_t, int64_t>>(m, "ga")
        .def(py::init<size_t, size_t, const std::vector<int64_t>&, size_t, problem_type>())
        .def("get_population_size", &ga<int64_t, int64_t>::get_population_size);
}
