import argparse
import json
import struct
from typing import TYPE_CHECKING, cast

import unrealsdk
from command_extensions import autoregister
from command_extensions.builtins import obj_name_splitter, parse_object
from mods_base import command
from unrealsdk.unreal import WrappedStruct

from ._bpd_vars_native import structs
from .behavior_variable import BehaviorVariable
from .math_operators import EBinaryMathOperation, EUnaryMathOperation
from .struct_builders import (
    JSONDict,
    build_bv_attachment_location,
    build_bv_attribute,
    build_bv_binary_math,
    build_bv_direction_vector,
    build_bv_flag,
    build_bv_instance,
    build_bv_vector,
    build_unary_math,
)

if TYPE_CHECKING:
    from ._bpd_vars_native._enums import EBehaviorVariableType
else:
    EBehaviorVariableType = unrealsdk.find_enum("EBehaviorVariableType")

EDirectionRelativeToParent = unrealsdk.find_enum("EDirectionRelativeToParent")


def update_variable_from_dict(variable: BehaviorVariable, data: JSONDict) -> None:  # noqa: C901, PLR0912
    if new_name := data.get("Name"):
        variable.name = new_name
    if new_type := data.get("Type"):
        variable.variable_type = EBehaviorVariableType[new_type]
    if (new_value := data.get("Value")) is None:
        return
    match variable.variable_type:
        case EBehaviorVariableType.BVAR_Bool:
            variable.value = bool(new_value)

        case EBehaviorVariableType.BVAR_Int:
            variable.value = int(new_value)

        case EBehaviorVariableType.BVAR_Float:
            variable.value = float(new_value)

        case EBehaviorVariableType.BVAR_Object:
            variable.value = unrealsdk.find_object("Object", new_value)

        case EBehaviorVariableType.BVAR_Vector:
            variable.value = build_bv_vector(new_value)

        case EBehaviorVariableType.BVAR_Attribute:
            variable.value = build_bv_attribute(new_value)

        case EBehaviorVariableType.BVAR_InstanceData:
            variable.value = build_bv_instance(new_value)

        case EBehaviorVariableType.BVAR_DirectionVector:
            variable.value = build_bv_direction_vector(new_value)

        case EBehaviorVariableType.BVAR_AttachmentLocation:
            variable.value = build_bv_attachment_location(new_value)

        case EBehaviorVariableType.BVAR_UnaryMath:
            variable.value = build_unary_math(new_value)

        case EBehaviorVariableType.BVAR_BinaryMath:
            variable.value = build_bv_binary_math(new_value)

        case EBehaviorVariableType.BVAR_Flag:
            variable.value = build_bv_flag(new_value)


@autoregister
@command(splitter=obj_name_splitter)
def set_variable(args: argparse.Namespace) -> None:
    bpd = parse_object(args.bpd)
    sequence_idx = args.sequence_idx
    if sequence_idx >= len(bpd.BehaviorSequences):
        unrealsdk.logging.error(f"sequence index {sequence_idx} is out of range for {bpd}")
        return
    sequence = bpd.BehaviorSequences[sequence_idx]
    variable_idx = args.variable_idx
    if variable_idx > len(sequence.VariableData):
        unrealsdk.logging.error(
            f"variable index {variable_idx} is out of range for {bpd}[{sequence_idx}]"
        )
        return
    try:
        data = json.loads(args.variable_value)
    except Exception as e:  # noqa: BLE001
        # Don't raise errors during command handling, need to continue on.
        unrealsdk.logging.error(f"Failed to decode {args.variable_value}")
        unrealsdk.logging.error(e)
        return
    if variable_idx == len(sequence.VariableData):
        var = BehaviorVariable(unrealsdk.make_struct("BehaviorVariableData"))
        update_variable_from_dict(var, cast("JSONDict", data))
        sequence.VariableData.append(var.variable)
        return
    update_variable_from_dict(
        BehaviorVariable(sequence.VariableData[variable_idx]), cast("JSONDict", data)
    )


set_variable.add_argument("bpd")
set_variable.add_argument("sequence_idx", type=int)
set_variable.add_argument("variable_idx", type=int)
set_variable.add_argument("variable_value")


@autoregister
@command(splitter=obj_name_splitter)
def set_variable_data(args: argparse.Namespace) -> None:
    bpd = parse_object(args.bpd)
    sequence_idx = args.sequence_idx
    if sequence_idx >= len(bpd.BehaviorSequences):
        unrealsdk.logging.error(f"sequence index {sequence_idx} is out of range for {bpd}")
        return
    sequence = bpd.BehaviorSequences[sequence_idx]
    try:
        data = json.loads(args.variable_data)
    except Exception as e:  # noqa: BLE001
        # Don't raise errors during command handling, need to continue on.
        unrealsdk.logging.error(f"Failed to decode {args.variable_data}")
        unrealsdk.logging.error(e)
        return

    variable_data = []
    for var_value in data:
        var = BehaviorVariable(unrealsdk.make_struct("BehaviorVariableData"))
        update_variable_from_dict(var, cast("JSONDict", var_value))
        variable_data.append(var.variable)
    sequence.VariableData = variable_data


set_variable_data.add_argument("bpd")
set_variable_data.add_argument("sequence_idx", type=int)
set_variable_data.add_argument("variable_data")


def parse_arrayindexandlength(number: int) -> tuple[int, int]:
    """Return an array index and length tuple for the given number."""
    number = int(number)
    byteval = struct.pack(">i", number)
    return struct.unpack(">HH", byteval)


def lookup_variable_indexes(sequence: WrappedStruct, idx_len: int) -> str:
    index, length = parse_arrayindexandlength(idx_len)
    variables = []
    for x in range(length):
        vidx = sequence.ConsolidatedLinkedVariables[index + x]
        variables.append(f"[{vidx}]{sequence.VariableData[vidx].name}")
    if len(variables) == 1:
        return variables[0]
    return f"({','.join(variables)})"


def variable_value_to_string(sequence: WrappedStruct, variable: BehaviorVariable) -> str:  # noqa: PLR0911
    """Convert the variable value to a string.

    Converts any subarray data properties into the index and name.

    """
    value = variable.value
    match value:
        case structs.BVAttributeData():
            context = lookup_variable_indexes(sequence, value.ContextVariable.ArrayIndexAndLength)
            return f"(ContextVariable: {context}, Value: {value.Value})"

        case structs.BVDirectionVectorData():
            parent = lookup_variable_indexes(sequence, value.ParentVariable.ArrayIndexAndLength)
            direction_var = lookup_variable_indexes(
                sequence, value.DefaultDirectionVariable.ArrayIndexAndLength
            )
            cone_var = lookup_variable_indexes(sequence, value.ConeVariable.ArrayIndexAndLength)
            return (
                f"(Direction: {EDirectionRelativeToParent(value.Direction).name}, "
                f"ParentVariable: {parent}, "
                f"DefaultDirection: {value.DefaultDirection}, "
                f"DefaultDirectionVariable: {direction_var}, "
                f"AdditionalRotation: {value.AdditionalRotation}, "
                f"DefaultConeAroundDirection: {value.DefaultConeAroundDirection}, "
                f"ConeVariable: {cone_var})"
            )

        case structs.BVAttachmentLocationData():
            source = lookup_variable_indexes(sequence, value.SourceVariable.ArrayIndexAndLength)
            location_var = lookup_variable_indexes(
                sequence, value.DefaultLocationVariable.ArrayIndexAndLength
            )
            return (
                f"(SourceVariable: {source}, "
                f"bDefaultToSourceLocation: {value.bDefaultToSourceLocation}, "
                f"DefaultLocation: {value.DefaultLocation}, "
                f"DefaultLocationVariable: {location_var})"
            )

        case structs.BVInstanceDataData():
            context = lookup_variable_indexes(sequence, value.ContextVariable.ArrayIndexAndLength)
            return f"(ContextVariable: {context}, Value: {value.InstanceDataName})"

        case structs.BVBinaryMathData():
            a = lookup_variable_indexes(sequence, value.OperandA.ArrayIndexAndLength)
            b = lookup_variable_indexes(sequence, value.OperandB.ArrayIndexAndLength)
            operation = EBinaryMathOperation(value.Operation).name
            return f"(OperandA: {a}, OperandB: {b}, Operation: {operation})"

        case structs.BVUnaryMathData():
            operand = lookup_variable_indexes(sequence, value.Operand.ArrayIndexAndLength)
            operation = EUnaryMathOperation._EAll(value.Operation).name
            return f"(ContextVariable: {operand}, Operation: {operation})"

        case structs.BVFlagData():
            context = lookup_variable_indexes(sequence, value.ContextVariable.ArrayIndexAndLength)
            return f"(ContextVariable: {context}, FlagDef: {value.FlagDef})"

        case _:
            return str(value)


@autoregister
@command(splitter=obj_name_splitter)
def print_variables(args: argparse.Namespace) -> None:
    bpd = parse_object(args.bpd)
    sequence_idx = args.sequence_idx
    if sequence_idx is None:
        sequences = bpd.BehaviorSequences
    else:
        if sequence_idx >= len(bpd.BehaviorSequences):
            unrealsdk.logging.error(f"sequence index {sequence_idx} is out of range for {bpd}")
            return
        sequences = [bpd.BehaviorSequences[sequence_idx]]

    for sequence in sequences:
        for idx, v in enumerate(sequence.VariableData):
            variable = BehaviorVariable(v)
            unrealsdk.logging.info(
                idx,
                f"{variable.name}",
                f"{variable.variable_type.name[5:]}",  # Trim BVAR_
                variable_value_to_string(sequence, variable),
            )


print_variables.add_argument("bpd")
print_variables.add_argument("-s", "--sequence_idx", type=int)
