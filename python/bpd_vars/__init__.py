from mods_base import Library, build_mod

from .behavior_variable import BehaviorVariable
from .commands import set_variable

__all__ = ["BehaviorVariable"]


build_mod(cls=Library, commands=[set_variable])
