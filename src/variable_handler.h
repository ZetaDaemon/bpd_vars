#pragma once
#include "types/structs.h"

#include <pybind11/pybind11.h>

namespace bpd_vars
{
py::object get_behavior_variable_data(py::object variable);

void change_variable_value(py::object variable, py::object new_value);

void change_variable_type(py::object variable, uint8_t variable_type);
} // namespace bpd_vars