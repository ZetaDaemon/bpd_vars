#include "bindings/struct_bindings.h"
#include "variable_handler.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(bpd_vars_native, m)
{
    m.doc() = "Native functions for bpd_vars";

    m.def("version", []() { return "bpd_vars native 0.1"; }, "Returns native module version.");

    m.def("get_behavior_variable_data",
          &bpd_vars::get_behavior_variable_data,
          "Gets BehaviorVariableData Value.Data.");

    bpd_vars::bindings::bind_structs(m);
}