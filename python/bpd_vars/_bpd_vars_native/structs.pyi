from unrealsdk.unreal import UObject

from ._common import AttributeInitializationData, Rotator, SubarrayData, Vector
from ._enums import EDirectionRelativeToParent

class BVVector:
    Value: Vector

    def __init__(self, Value: Vector | None = None) -> None: ...

class BVAttributeData:
    ContextVariable: SubarrayData
    Value: AttributeInitializationData

    def __init__(
        self,
        ContextVariable: SubarrayData | None = None,
        Value: AttributeInitializationData | None = None,
    ) -> None: ...

class BVDirectionVectorData:
    Direction: EDirectionRelativeToParent
    ParentVariable: SubarrayData
    DefaultDirection: Vector
    DefaultDirectionVariable: SubarrayData
    AdditionalRotation: Rotator
    DefaultConeAroundDirection: float
    ConeVariable: SubarrayData

    def __init__(
        self,
        Direction: EDirectionRelativeToParent = ...,
        ParentVariable: SubarrayData | None = None,
        DefaultDirection: Vector | None = None,
        DefaultDirectionVariable: SubarrayData | None = None,
        AdditionalRotation: Rotator | None = None,
        DefaultConeAroundDirection: float = 0.0,
        ConeVariable: SubarrayData | None = None,
    ) -> None: ...

class BVAttachmentLocationData:
    SourceVariable: SubarrayData
    bDefaultToSourceLocation: int
    DefaultLocation: Vector
    DefaultLocationVariable: SubarrayData

    def __init__(
        self,
        SourceVariable: SubarrayData | None = None,
        bDefaultToSourceLocation: int = 0,
        DefaultLocation: Vector | None = None,
        DefaultLocationVariable: SubarrayData | None = None,
    ) -> None: ...

class BVInstanceDataData:
    ContextVariable: SubarrayData
    InstanceDataName: str

    def __init__(
        self, ContextVariable: SubarrayData | None = None, InstanceDataName: str = "None"
    ) -> None: ...

class BVBinaryMathData:
    OperandA: SubarrayData
    OperandB: SubarrayData
    Operation: int  # EBinaryMathOperation

    def __init__(
        self,
        OperandA: SubarrayData | None = None,
        OperandB: SubarrayData | None = None,
        Operation: int = 0,  # EBinaryMathOperation = ...,
    ) -> None: ...

class BVUnaryMathData:
    Operand: SubarrayData
    Operation: int

    def __init__(self, Operand: SubarrayData | None = None, Operation: int = 0) -> None: ...

class BVFlagData:
    ContextVariable: SubarrayData
    FlagDef: UObject
    """GearboxFramework.FlagDefinition"""

    def __init__(
        self, ContextVariable: SubarrayData | None = None, FlagDef: UObject | None = None
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
