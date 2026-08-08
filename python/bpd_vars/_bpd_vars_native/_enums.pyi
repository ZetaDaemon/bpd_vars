from enum import IntEnum

class EBehaviorVariableType(IntEnum):
    """GearboxFramework.BehaviorProviderDefinition:EBehaviorVariableType."""

    BVAR_None = 0
    BVAR_Bool = 1
    BVAR_Int = 2
    BVAR_Float = 3
    BVAR_Vector = 4
    BVAR_Object = 5
    BVAR_AllPlayers = 6
    BVAR_Attribute = 7
    BVAR_InstanceData = 8
    BVAR_NamedVariable = 9
    BVAR_NamedKismetVariable = 10
    BVAR_DirectionVector = 11
    BVAR_AttachmentLocation = 12
    BVAR_UnaryMath = 13
    BVAR_BinaryMath = 14
    BVAR_Flag = 15
    BVAR_MAX = 16

class EDirectionRelativeToParent(IntEnum):
    """GearboxFramework.BehaviorHelpers:EDirectionRelativeToParent."""

    DIRECTION_Default = 0
    DIRECTION_ParentOrientation = 1
    DIRECTION_InverseParentOrientation = 2
    DIRECTION_ParentVelocity = 3
    DIRECTION_InverseParentVelocity = 4
    DIRECTION_Random = 5
    DIRECTION_RandomUpwards = 6
    DIRECTION_RandomDownwards = 7
    DIRECTION_RandomOnHorizontalPlane = 8
    DIRECTION_StraightUp = 9
    DIRECTION_StraightDown = 10
    DIRECTION_StraightTowardTarget = 11
    DIRECTION_ParentAimDirection = 12
    DIRECTION_InverseParentAimDirection = 13
    DIRECTION_InverseTearOffMomentum = 14
    DIRECTION_MAX = 15

class EBinaryMathOperation(IntEnum):
    """WillowGame.Behavior_SimpleMath:EBinaryMathOperation."""

    BINARYMATH_Add = 0
    BINARYMATH_Sub = 1
    BINARYMATH_Mul = 2
    BINARYMATH_Div = 3
    BINARYMATH_Pow = 4
    BINARYMATH_Rand = 5
    BINARYMATH_Avg = 6
    BINARYMATH_Min = 7
    BINARYMATH_Maximum = 8
    BINARYMATH_NoChange = 9
    BINARYMATH_MAX = 10
