#pragma once

#include "enums.h"
#include "unrealsdk/unreal/classes/uobject.h"
#include "unrealsdk/unreal/structs/fname.h"

namespace bpd_vars::structs
{
struct BVVector;
struct BVAttributeData;
struct BVDirectionVectorData;
struct BVAttachmentLocationData;
struct BVInstanceDataData;
struct BVBinaryMathData;
struct BVUnaryMathData;
struct BVFlagData;
} // namespace bpd_vars::structs

namespace bpd_vars::common
{

struct SubarrayData
{
    int ArrayIndexAndLength;
};
static_assert(sizeof(SubarrayData) == 0x4);

struct Vector
{
    float X;
    float Y;
    float Z;
};
static_assert(sizeof(Vector) == 0xC);

struct Rotator
{
    float Pitch;
    float Yaw;
    float Roll;
};
static_assert(sizeof(Rotator) == 0xC);

struct AttributeInitializationData
{
    float BaseValueConstant;
    unrealsdk::unreal::UObject *BaseValueAttribute;
    unrealsdk::unreal::UObject *InitializationDefinition;
    float BaseValueScaleConstant;
};
static_assert(sizeof(AttributeInitializationData) == 0x10);

union BehaviorVariableDataValue {
    uint32_t BoolValue;
    int32_t IntValue;
    float FloatValue;
    unrealsdk::unreal::UObject *ObjectValue;
    structs::BVVector *VectorValue;
    structs::BVAttributeData *AttributeValue;
    structs::BVDirectionVectorData *DirectionVectorValue;
    structs::BVAttachmentLocationData *AttachmentLocationValue;
    structs::BVInstanceDataData *InstanceDataValue;
    structs::BVBinaryMathData *BinaryMathValue;
    structs::BVUnaryMathData *UnaryMathValue;
    structs::BVFlagData *FlagValue;
};
static_assert(sizeof(BehaviorVariableDataValue) == 0x4);

struct BehaviorVariableData
{
    unrealsdk::unreal::FName Name;
    enums::EBehaviorVariableType Type;
    uint8_t Padding[3];
    BehaviorVariableDataValue Value;
};
static_assert(sizeof(BehaviorVariableData) == 0x10);
} // namespace bpd_vars::common