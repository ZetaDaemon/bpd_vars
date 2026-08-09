import argparse
import json
from typing import TYPE_CHECKING, cast

import unrealsdk
from command_extensions import autoregister
from command_extensions.builtins import obj_name_splitter
from mods_base import command

from .behavior_variable import BehaviorVariable
from .struct_builders import (
    JSONDict,
    build_bv_attachment_location,
    build_bv_attribute,
    build_bv_binary_math,
    build_bv_direction_vector,
    build_bv_flag,
    build_bv_instance,
    build_unary_math,
    build_bv_vector,
)

if TYPE_CHECKING:
    from ._bpd_vars_native._enums import EBehaviorVariableType
else:
    EBehaviorVariableType = unrealsdk.find_enum("EBehaviorVariableType")


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
def update_variable(args: argparse.Namespace) -> None:
    bpd = unrealsdk.find_object("Object", args.bpd)
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
        data = json.loads(args.variable_data)
    except Exception as e:  # noqa: BLE001
        # Don't raise errors during command handling, need to continue on.
        unrealsdk.logging.error(f"Failed to decode {args.variable_data}")
        unrealsdk.logging.error(e)
        return
    if variable_idx == len(sequence.VariableData):
        var = BehaviorVariable(unrealsdk.make_struct("BehaviorVariableData"))
        update_variable_from_dict(var, cast("JSONDict", data))
        sequence.VariableData.append(var)
        return
    update_variable_from_dict(
        BehaviorVariable(sequence.VariableData[variable_idx]), cast("JSONDict", data)
    )


update_variable.add_argument("bpd")
update_variable.add_argument("sequence_idx", type=int)
update_variable.add_argument("variable_idx", type=int)
update_variable.add_argument("variable_data")
