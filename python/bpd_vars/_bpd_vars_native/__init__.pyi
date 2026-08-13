from ._common import BehaviorVariableData
from ._enums import EBehaviorVariableType
from .structs import BehaviorVariableDataValue

def get_behavior_variable_data(variable: BehaviorVariableData) -> BehaviorVariableDataValue:
    """Get the value stored in a BehaviorVariableData.

    Args:
        variable: A wrapped ``BehaviorVariableData`` struct.

    Returns:
        The decoded variable value.

    """

def change_variable_value(
    variable: BehaviorVariableData, new_value: BehaviorVariableDataValue
) -> None:
    """Change the value stored in a BehaviorVariableData.

    A copy of ``new_value`` is assigned to the variable.
    The value must match the variable's existing type.

    Args:
        variable: A wrapped ``BehaviorVariableData`` struct.
        new_value: The value to store.

    """

def change_variable_type(
    variable: BehaviorVariableData, variable_type: EBehaviorVariableType
) -> None:
    """Change the type of data stored in a BehaviorVariableData.

    The value is initialized to its default value.

    Args:
        variable: A wrapped ``BehaviorVariableData`` struct.
        variable_type: The new type of data to store.

    """
