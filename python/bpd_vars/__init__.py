from mods_base import Library, build_mod

from . import math_operators
from .behavior_variable import BehaviorVariable
from .commands import print_variables, set_variable, set_variable_data

__all__ = ["BehaviorVariable", "math_operators"]


build_mod(cls=Library, commands=[set_variable, print_variables, set_variable_data])
