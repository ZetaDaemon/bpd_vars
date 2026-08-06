#pragma once

#include <cstdint>

#include "common.h"
#include "enums.h"
#include "unrealsdk/unreal/classes/uobject.h"
#include "unrealsdk/unreal/structs/fname.h"

using namespace unrealsdk::unreal;

namespace bpd_vars::structs
{

struct BVVector
{
    common::Vector Value;
};
static_assert(sizeof(BVVector) == 0xC);

struct BVAttributeData
{
    common::SubarrayData ContextVariable;
    common::AttributeInitializationData Value;
};
static_assert(sizeof(BVAttributeData) == 0x14);

struct BVDirectionVectorData
{
    enums::EDirectionRelativeToParent Direction;
    uint8_t Padding[3];
    common::SubarrayData ParentVariable;
    common::Vector DefaultDirection;
    common::SubarrayData DefaultDirectionVariable;
    common::Rotator AdditionalRotation;
    float DefaultConeAroundDirection;
    common::SubarrayData ConeVariable;
};
static_assert(sizeof(BVDirectionVectorData) == 0x2C);

struct BVAttachmentLocationData
{
    common::SubarrayData SourceVariable;
    FName AttachmentName;
    uint32_t bDefaultToSourceLocation;
    common::Vector DefaultLocation;
    common::SubarrayData DefaultLocationVariable;
};
static_assert(sizeof(BVAttachmentLocationData) == 0x20);

struct BVInstanceDataData
{
    common::SubarrayData ContextVariable;
    FName InstanceDataName;
};
static_assert(sizeof(BVInstanceDataData) == 0xC);

struct BVBinaryMathData
{
    common::SubarrayData OperandA;
    common::SubarrayData OperandB;
    enums::EBinaryMathOperation Operation;
};
static_assert(sizeof(BVBinaryMathData) == 0xC);

struct BVUnaryMathData
{
    common::SubarrayData Operand;
    int32_t Operation;
};
static_assert(sizeof(BVUnaryMathData) == 0x8);

struct BVFlagData
{
    common::SubarrayData ContextVariable;
    UObject *FlagDef;
};
static_assert(sizeof(BVFlagData) == 0x8);

union BehaviorVariableDataValue {
    uint32_t BoolValue;
    int32_t IntValue;
    float FloatValue;
    UObject *ObjectValue;
    BVVector *VectorValue;
    BVAttributeData *AttributeValue;
    BVDirectionVectorData *DirectionVectorValue;
    BVAttachmentLocationData *AttachmentLocationValue;
    BVInstanceDataData *InstanceDataValue;
    BVBinaryMathData *BinaryMathValue;
    BVUnaryMathData *UnaryMathValue;
    BVFlagData *FlagValue;
};
static_assert(sizeof(BehaviorVariableDataValue) == 0x4);

struct BehaviorVariableData
{
    FName Name;
    enums::EBehaviorVariableType Type;
    uint8_t Padding[3];
    BehaviorVariableDataValue Value;
};
static_assert(sizeof(BehaviorVariableData) == 0x10);
} // namespace bpd_vars::structs