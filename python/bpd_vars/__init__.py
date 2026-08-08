from . import _bpd_vars_native
from .behavior_variable import BehaviorVariable

__all__ = ["BehaviorVariable"]

print(_bpd_vars_native.version())
