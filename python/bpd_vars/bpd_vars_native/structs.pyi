from unrealsdk.unreal import UObject

from ._common import AttributeInitializationData, Rotator, SubArrayData, Vector
from ._enums import EBehaviorVariableType, EBinaryMathOperation, EDirectionRelativeToParent

class BVWrappedStruct:
    Value: Vector

class BVAttributeData:
    ContextVariable: SubArrayData
    Value: AttributeInitializationData

class BVDirectionWrappedStructData:
    Direction: EDirectionRelativeToParent
    ParentVariable: SubArrayData
    DefaultDirection: Vector
    DefaultDirectionVariable: SubArrayData
    AdditionalRotation: Rotator
    DefaultConeAroundDirection: float
    ConeVariable: Vector

class BVAttachmentLocationData:
    SourceVariable: SubArrayData
    bDefaultToSourceLocation: int
    DefaultLocation: Vector
    DefaultLocationVariable: SubArrayData

class BVInstanceDataData:
    ContextVariable: SubArrayData
    InstanceDataName: str

class BVBinaryMathData:
    OperandA: SubArrayData
    OperandB: SubArrayData
    Operation: EBinaryMathOperation

class BVUnaryMathData:
    Operand: SubArrayData
    Operation: int

class BVFlagData:
    ContextVariable: SubArrayData
    FlagDef: UObject
    """GearboxFramework.FlagDefinition"""

class BehaviorVariableData:
    Name: str
    Type: EBehaviorVariableType

type BehaviorVariableDataValue = (
    int
    | float
    | bool
    | UObject
    | BVWrappedStruct
    | BVAttributeData
    | BVDirectionWrappedStructData
    | BVAttachmentLocationData
    | BVInstanceDataData
    | BVBinaryMathData
    | BVUnaryMathData
    | BVFlagData
    | None
)
