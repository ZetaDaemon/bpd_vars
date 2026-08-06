#pragma once

#include "unrealsdk/unreal/classes/uobject.h"

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

} // namespace bpd_vars::common