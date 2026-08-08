from unrealsdk.unreal import UObject

from ._common import AttributeInitializationData, Rotator, SubArrayData, Vector
from ._enums import EBinaryMathOperation, EDirectionRelativeToParent

class BVVector:
    Value: Vector

    def __init__(self, Value: Vector | None = None) -> None: ...

class BVAttributeData:
    ContextVariable: SubArrayData
    Value: AttributeInitializationData

    def __init__(
        self,
        ContextVariable: SubArrayData | None = None,
        Value: AttributeInitializationData | None = None,
    ) -> None: ...

class BVDirectionVectorData:
    Direction: EDirectionRelativeToParent
    ParentVariable: SubArrayData
    DefaultDirection: Vector
    DefaultDirectionVariable: SubArrayData
    AdditionalRotation: Rotator
    DefaultConeAroundDirection: float
    ConeVariable: SubArrayData

    def __init__(
        self,
        Direction: EDirectionRelativeToParent = ...,
        ParentVariable: SubArrayData | None = None,
        DefaultDirection: Vector | None = None,
        DefaultDirectionVariable: SubArrayData | None = None,
        AdditionalRotation: Rotator | None = None,
        DefaultConeAroundDirection: float = 0.0,
        ConeVariable: SubArrayData | None = None,
    ) -> None: ...

class BVAttachmentLocationData:
    SourceVariable: SubArrayData
    bDefaultToSourceLocation: int
    DefaultLocation: Vector
    DefaultLocationVariable: SubArrayData

    def __init__(
        self,
        SourceVariable: SubArrayData | None = None,
        bDefaultToSourceLocation: int = 0,
        DefaultLocation: Vector | None = None,
        DefaultLocationVariable: SubArrayData | None = None,
    ) -> None: ...

class BVInstanceDataData:
    ContextVariable: SubArrayData
    InstanceDataName: str

    def __init__(
        self, ContextVariable: SubArrayData | None = None, InstanceDataName: str = "None"
    ) -> None: ...

class BVBinaryMathData:
    OperandA: SubArrayData
    OperandB: SubArrayData
    Operation: EBinaryMathOperation

    def __init__(
        self,
        OperandA: SubArrayData | None = None,
        OperandB: SubArrayData | None = None,
        Operation: EBinaryMathOperation = ...,
    ) -> None: ...

class BVUnaryMathData:
    Operand: SubArrayData
    Operation: int

    def __init__(self, Operand: SubArrayData | None = None, Operation: int = 0) -> None: ...

class BVFlagData:
    ContextVariable: SubArrayData
    FlagDef: UObject
    """GearboxFramework.FlagDefinition"""

    def __init__(
        self, ContextVariable: SubArrayData | None = None, FlagDef: UObject | None = None
    ) -> None: ...

type BehaviorVariableDataValue = (
    int
    | float
    | bool
    | UObject
    | BVVector
    | BVAttributeData
    | BVDirectionVectorData
    | BVAttachmentLocationData
    | BVInstanceDataData
    | BVBinaryMathData
    | BVUnaryMathData
    | BVFlagData
    | None
)
