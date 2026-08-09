from mods_base import Library, build_mod

from .behavior_variable import BehaviorVariable
from .commands import update_variable

__all__ = ["BehaviorVariable"]


build_mod(cls=Library, commands=[update_variable])
