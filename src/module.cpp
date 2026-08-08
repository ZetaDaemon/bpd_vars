#include "bindings/struct_bindings.h"
#include "variable_handler.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(_bpd_vars_native, m)
{
    m.doc() = "Native functions for bpd_vars";

    m.def("version", []() { return "bpd_vars native 1.0"; }, "Returns native module version.");

    m.def("get_behavior_variable_data",
          &bpd_vars::get_behavior_variable_data,
          py::arg("variable"),
          "Gets BehaviorVariableData Value.");

    m.def("change_variable_value",
          &bpd_vars::change_variable_value,
          py::arg("variable"),
          py::arg("new_value"),
          "Change the value stored in a BehaviorVariableData.");

    m.def("change_variable_type",
          &bpd_vars::change_variable_type,
          py::arg("variable"),
          py::arg("variable_type"),
          "Change the type stored in a BehaviorVariableData.");

    bpd_vars::bindings::bind_structs(m);
}