from . import bpd_vars_native
from .bpd_vars_native import get_behavior_variable_data, structs

__all__ = ["get_behavior_variable_data", "structs"]

print(bpd_vars_native.version())
