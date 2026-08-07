from .structs import BehaviorVariableData, BehaviorVariableDataValue

def get_behavior_variable_data(
    variable_data: BehaviorVariableData,
) -> BehaviorVariableDataValue:
    """Get the value stored in a BehaviorVariableData.

    Args:
        variable_data: A WrappedStruct containing BehaviorVariableData.

    Returns:
        The decoded variable value.

    """

def version() -> str:
    "Gets the native module version"
