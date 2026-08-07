from unrealsdk.unreal import UObject, WrappedStruct

class SubArrayData(WrappedStruct):
    """Wrapped GearboxFramework.BehaviorProviderDefinition:SubarrayData."""

    ArrayIndexAndLength: int

class Vector(WrappedStruct):
    """Wrapped Core.Object:Vector."""

    X: float
    Y: float
    Z: float

class Rotator(WrappedStruct):
    """Wrapped Core.Object:Rotator."""

    Pitch: float
    Yaw: float
    Roll: float

class AttributeInitializationData(WrappedStruct):
    """Wrapped Engine.AttributeInitializationDefinition:AttributeInitializationData."""

    BaseValueConstant: float
    BaseValueAttribute: UObject
    """Engine.AttributeDefinition"""
    InitializationDefinition: UObject
    """Engine.AttributeInitializationDefinition"""
    BaseValueScaleConstant: float
