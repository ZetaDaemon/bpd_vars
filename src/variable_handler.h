#pragma once
#include "types/structs.h"

#include <pybind11/pybind11.h>

namespace bpd_vars
{
py::object get_behavior_variable_data(py::object obj);

void change_variable_value(py::object obj, py::object new_value);

void change_variable_type(py::object obj, uint8_t type, py::object new_value);
} // namespace bpd_vars