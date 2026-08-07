#pragma once

#include <pybind11/pybind11.h>

namespace bpd_vars
{
    py::object get_behavior_variable_data(py::object obj);
}