#pragma once

#include <pybind11/pybind11.h>
namespace bpd_vars::bindings
{
void bind_structs(pybind11::module_ &m);
} // namespace bpd_vars::bindings