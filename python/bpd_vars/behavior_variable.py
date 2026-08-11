from __future__ import annotations

from typing import TYPE_CHECKING

import unrealsdk

from . import _bpd_vars_native

if TYPE_CHECKING:
    from unrealsdk.unreal import WrappedStruct

    from ._bpd_vars_native import _enums, structs
    from ._bpd_vars_native._common import BehaviorVariableData

VARIABLE_DATA_STRUCT = unrealsdk.find_object(
    "ScriptStruct", "GearboxFramework.BehaviorProviderDefinition:BehaviorVariableData"
)


class BehaviorVariable:
    """A wrapper around BehaviorVariableData."""

    _variable: BehaviorVariableData

    def __init__(self, variable: WrappedStruct) -> None:
        """Construct a BehaviorVariable for a BehaviorVariableData."""
        if variable._type != VARIABLE_DATA_STRUCT:
            msg = "variable must be a BehaviorVariableData struct."
            raise ValueError(msg)
        self._variable = variable

    @property
    def name(self) -> str:
        """Get the variable name."""
        return self._variable.Name

    @name.setter
    def name(self, name: str) -> None:
        """Set the variable name."""
        self._variable.Name = name

    @property
    def variable_type(self) -> _enums.EBehaviorVariableType:
        """Get the variable type."""
        return self._variable.Type

    @variable_type.setter
    def variable_type(self, new_type: _enums.EBehaviorVariableType) -> None:
        """Set variable type.

        The Value of the BehaviorVariableData is reset to a default value for the new type.
        """
        _bpd_vars_native.change_variable_type(self._variable, new_type)

    @property
    def value(self) -> structs.BehaviorVariableDataValue:
        """Get the internal value."""
        return _bpd_vars_native.get_behavior_variable_data(self._variable)

    @value.setter
    def value(self, new_value: structs.BehaviorVariableDataValue) -> None:
        """Set the internal value."""
        _bpd_vars_native.change_variable_value(self._variable, new_value)

    @property
    def variable(self) -> BehaviorVariableData:
        """Get the BehaviorVariableData.

        There is no setter for this.
        """
        return self._variable
