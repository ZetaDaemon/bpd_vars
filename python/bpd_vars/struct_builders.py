from dataclasses import dataclass
from typing import TYPE_CHECKING

import unrealsdk
from unrealsdk.unreal import WrappedStruct

from ._bpd_vars_native import structs

if TYPE_CHECKING:
    from ._bpd_vars_native._enums import EBehaviorVariableType
else:
    EBehaviorVariableType = unrealsdk.find_enum("EBehaviorVariableType")
    EDirectionRelativeToParent = unrealsdk.find_enum("EDirectionRelativeToParent")
    EBinaryMathOperation = unrealsdk.find_enum("EBinaryMathOperation")


type JSONDict = dict[str, "JSONValue"]
type JSONList = list["JSONValue"]
type JSONValue = str | int | float | bool | JSONDict | JSONList | None
type JSONValueNotList = str | int | float | bool | JSONDict | None


def build_vector(data: JSONValueNotList) -> WrappedStruct:
    vector = unrealsdk.make_struct("Vector")
    if x := data.get("X"):
        vector.X = float(x)

    if y := data.get("Y"):
        vector.Y = float(y)

    if z := data.get("Z"):
        vector.Z = float(z)

    return vector


def build_rotator(data: JSONValueNotList) -> WrappedStruct:
    rotator = unrealsdk.make_struct("Rotator")
    if pitch := data.get("Pitch"):
        rotator.Pitch = float(pitch)

    if yaw := data.get("Yaw"):
        rotator.Yaw = float(yaw)

    if roll := data.get("Roll"):
        rotator.Roll = float(roll)

    return rotator


def build_subarray(data: JSONValueNotList) -> WrappedStruct:
    subarray = unrealsdk.make_struct("SubarrayData")
    if ail := data.get("ArrayIndexAndLength"):
        subarray.ArrayIndexAndLength = int(ail)
    return subarray


def build_initdata(data: JSONValueNotList) -> WrappedStruct:
    initdata = unrealsdk.make_struct("AttributeInitializationData")
    if constant := data.get("BaseValueConstant"):
        initdata.BaseValueConstant = float(constant)

    if attr := data.get("BaseValueAttribute"):
        initdata.BaseValueAttribute = unrealsdk.find_object("AttributeDefinition", attr)

    if initdef := data.get("InitializationDefinition"):
        initdata.InitializationDefinition = unrealsdk.find_object(
            "AttributeInitializationDefinition", initdef
        )

    if scale := data.get("BaseValueScaleConstant"):
        initdata.BaseValueScaleConstant = float(scale)

    return initdata


def build_bv_vector(data: JSONValueNotList) -> structs.BVVector:
    new_variable_value = structs.BVVector()
    if value := data.get("Value"):
        new_variable_value.Value = build_vector(value)
    return new_variable_value


def build_bv_attribute(data: JSONValueNotList) -> structs.BVAttributeData:
    new_variable_value = structs.BVAttributeData()
    if context := data.get("ContextVariable"):
        new_variable_value.ContextVariable = build_subarray(context)

    if initdata := data.get("Value"):
        new_variable_value.Value = build_initdata(initdata)

    return new_variable_value


def build_bv_instance(data: JSONValueNotList) -> structs.BVInstanceDataData:
    new_variable_value = structs.BVInstanceDataData()
    if context := data.get("ContextVariable"):
        new_variable_value.ContextVariable = build_subarray(context)

    if x := data.get("InstanceDataName"):
        new_variable_value.InstanceDataName = x

    return new_variable_value


def build_bv_direction_vector(data: JSONValueNotList) -> structs.BVDirectionVectorData:
    new_variable_value = structs.BVDirectionVectorData()
    if direction := data.get("Direction"):
        new_variable_value.Direction = EDirectionRelativeToParent[direction]

    if parent := data.get("ParentVariable"):
        new_variable_value.ParentVariable = build_subarray(parent)

    if default_dir := data.get("DefaultDirection"):
        new_variable_value.DefaultDirection = build_vector(default_dir)

    if default_dir_var := data.get("DefaultDirectionVariable"):
        new_variable_value.DefaultDirectionVariable = build_subarray(default_dir_var)

    if rotation := data.get("AdditionalRotation"):
        new_variable_value.AdditionalRotation = build_rotator(rotation)

    if default_cone := data.get("DefaultConeAroundDirection"):
        new_variable_value.DefaultConeAroundDirection = float(default_cone)

    if cone_var := data.get("ConeVariable"):
        new_variable_value.ConeVariable = build_subarray(cone_var)

    return new_variable_value


def build_bv_attachment_location(data: JSONValueNotList) -> structs.BVAttachmentLocationData:
    new_variable_value = structs.BVAttachmentLocationData()
    if source := data.get("SourceVariable"):
        new_variable_value.SourceVariable = build_subarray(source)

    if default_to_source := data.get("bDefaultToSourceLocation"):
        new_variable_value.bDefaultToSourceLocation = int(default_to_source)

    if location := data.get("DefaultLocation"):
        new_variable_value.DefaultLocation = build_vector(location)

    if location_var := data.get("DefaultLocationVariable"):
        new_variable_value.DefaultLocationVariable = build_subarray(location_var)

    return new_variable_value


def build_bv_binary_math(data: JSONValueNotList) -> structs.BVBinaryMathData:
    new_variable_value = structs.BVBinaryMathData()
    if opp_a := data.get("OperandA"):
        new_variable_value.OperandA = build_subarray(opp_a)

    if opp_b := data.get("OperandB"):
        new_variable_value.OperandB = build_subarray(opp_b)

    if x := data.get("Operation"):
        new_variable_value.Operation = EBinaryMathOperation[x]

    return new_variable_value


def build_unary_math(data: JSONValueNotList) -> structs.BVUnaryMathData:
    new_variable_value = structs.BVUnaryMathData()
    if opp := data.get("Operand"):
        new_variable_value.Operand = build_subarray(opp)

    if x := data.get("Operation"):
        new_variable_value.Operation = int(x)

    return new_variable_value


def build_bv_flag(data: JSONValueNotList) -> structs.BVFlagData:
    new_variable_value = structs.BVFlagData()
    if context := data.get("ContextVariable"):
        new_variable_value.ContextVariable = build_subarray(context)

    if x := data.get("FlagDef"):
        new_variable_value.FlagDef = unrealsdk.find_object("FlagDefinition", x)

    return new_variable_value
