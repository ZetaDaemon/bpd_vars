#pragma once

#include <cstdint>

#include "common.h"
#include "enums.h"
#include "unrealsdk/unreal/classes/uobject.h"
#include "unrealsdk/unreal/structs/fname.h"

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
    unrealsdk::unreal::FName AttachmentName;
    uint32_t bDefaultToSourceLocation;
    common::Vector DefaultLocation;
    common::SubarrayData DefaultLocationVariable;
};
static_assert(sizeof(BVAttachmentLocationData) == 0x20);

struct BVInstanceDataData
{
    common::SubarrayData ContextVariable;
    unrealsdk::unreal::FName InstanceDataName;
};
static_assert(sizeof(BVInstanceDataData) == 0xC);

struct BVBinaryMathData
{
    common::SubarrayData OperandA;
    common::SubarrayData OperandB;
    /*enums::EBinaryMathOperation*/ int32_t Operation;
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
    unrealsdk::unreal::UObject *FlagDef;
};
static_assert(sizeof(BVFlagData) == 0x8);

} // namespace bpd_vars::structs