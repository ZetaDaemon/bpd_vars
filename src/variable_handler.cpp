#include "variable_handler.h"
#include "pyunrealsdk/type_casters.h"
#include "types/common.h"
#include "types/enums.h"
#include "types/structs.h"
#include "unrealsdk/unreal/classes/uobject.h"
#include "unrealsdk/unreal/wrappers/wrapped_struct.h"
#include "unrealsdk/unrealsdk.h"
#include <pybind11/pybind11.h>

using namespace unrealsdk::unreal;

namespace bpd_vars
{
template <typename T> py::object struct_pointer_to_pyobj(T *pntr)
{
    if (pntr == nullptr)
    {
        return py::none();
    }

    return py::cast(pntr, py::return_value_policy::reference);
}
py::object get_behavior_variable_data(py::object variable)
{
    auto wrapped = pyunrealsdk::type_casters::cast<unrealsdk::unreal::WrappedStruct *>(variable);

    common::BehaviorVariableData *variable_data =
        reinterpret_cast<common::BehaviorVariableData *>(wrapped->base.get());
    switch (variable_data->Type)
    {
    case enums::EBehaviorVariableType::BVAR_Bool:
        return py::bool_(variable_data->Value.BoolValue != 0);

    case enums::EBehaviorVariableType::BVAR_Int:
        return py::int_(variable_data->Value.IntValue);

    case enums::EBehaviorVariableType::BVAR_Float:
        return py::float_(variable_data->Value.FloatValue);

    case enums::EBehaviorVariableType::BVAR_Object:
        if (variable_data->Value.ObjectValue == nullptr)
        {
            return py::none();
        }
        return pyunrealsdk::type_casters::cast(variable_data->Value.ObjectValue);

    case enums::EBehaviorVariableType::BVAR_Vector:
        return struct_pointer_to_pyobj(variable_data->Value.VectorValue);

    case enums::EBehaviorVariableType::BVAR_Attribute:
        return struct_pointer_to_pyobj(variable_data->Value.AttributeValue);

    case enums::EBehaviorVariableType::BVAR_DirectionVector:
        return struct_pointer_to_pyobj(variable_data->Value.DirectionVectorValue);

    case enums::EBehaviorVariableType::BVAR_AttachmentLocation:
        return struct_pointer_to_pyobj(variable_data->Value.AttachmentLocationValue);

    case enums::EBehaviorVariableType::BVAR_InstanceData:
        return struct_pointer_to_pyobj(variable_data->Value.InstanceDataValue);

    case enums::EBehaviorVariableType::BVAR_BinaryMath:
        return struct_pointer_to_pyobj(variable_data->Value.BinaryMathValue);

    case enums::EBehaviorVariableType::BVAR_UnaryMath:
        return struct_pointer_to_pyobj(variable_data->Value.UnaryMathValue);

    case enums::EBehaviorVariableType::BVAR_Flag:
        return struct_pointer_to_pyobj(variable_data->Value.FlagValue);

    default:
        return py::none();
    }
    return py::none();
}

template <typename T> T *copy_pyobj_to_struct_pointer(py::object obj)
{
    T *source = nullptr;
    void *memory;
    if (!obj.is_none())
    {
        source = obj.cast<T *>();
    }
    memory = unrealsdk::u_malloc(sizeof(T));
    if (memory == nullptr)
    {
        throw std::bad_alloc();
    }
    if (source == nullptr)
    {
        return new (memory) T{};
    }
    return new (memory) T(*source);
}

void change_variable_value_inner(common::BehaviorVariableData *variable_data, py::object new_value)
{
    switch (variable_data->Type)
    {
    case enums::EBehaviorVariableType::BVAR_Bool: {
        uint32_t value = 0;
        if (!new_value.is_none())
        {
            value = new_value.cast<bool>() ? 1 : 0;
        }
        variable_data->Value.BoolValue = value;
        break;
    }

    case enums::EBehaviorVariableType::BVAR_Int: {
        int32_t value = 0;
        if (!new_value.is_none())
        {
            value = new_value.cast<int32_t>();
        }
        variable_data->Value.IntValue = value;
        break;
    }

    case enums::EBehaviorVariableType::BVAR_Float: {
        float value = 0.0f;
        if (!new_value.is_none())
        {
            value = new_value.cast<float>();
        }
        variable_data->Value.FloatValue = value;
        break;
    }

    case enums::EBehaviorVariableType::BVAR_Object:
        if (new_value.is_none())
        {
            variable_data->Value.ObjectValue = nullptr;
            break;
        }
        variable_data->Value.ObjectValue = pyunrealsdk::type_casters::cast<UObject *>(new_value);
        break;

    case enums::EBehaviorVariableType::BVAR_Vector:
        variable_data->Value.VectorValue = copy_pyobj_to_struct_pointer<structs::BVVector>(new_value);
        break;

    case enums::EBehaviorVariableType::BVAR_Attribute:
        variable_data->Value.AttributeValue =
            copy_pyobj_to_struct_pointer<structs::BVAttributeData>(new_value);
        break;

    case enums::EBehaviorVariableType::BVAR_DirectionVector:
        variable_data->Value.DirectionVectorValue =
            copy_pyobj_to_struct_pointer<structs::BVDirectionVectorData>(new_value);
        break;

    case enums::EBehaviorVariableType::BVAR_AttachmentLocation:
        variable_data->Value.AttachmentLocationValue =
            copy_pyobj_to_struct_pointer<structs::BVAttachmentLocationData>(new_value);
        break;

    case enums::EBehaviorVariableType::BVAR_InstanceData:
        variable_data->Value.InstanceDataValue =
            copy_pyobj_to_struct_pointer<structs::BVInstanceDataData>(new_value);
        break;

    case enums::EBehaviorVariableType::BVAR_BinaryMath:
        variable_data->Value.BinaryMathValue =
            copy_pyobj_to_struct_pointer<structs::BVBinaryMathData>(new_value);
        break;

    case enums::EBehaviorVariableType::BVAR_UnaryMath:
        variable_data->Value.UnaryMathValue =
            copy_pyobj_to_struct_pointer<structs::BVUnaryMathData>(new_value);
        break;

    case enums::EBehaviorVariableType::BVAR_Flag:
        variable_data->Value.FlagValue = copy_pyobj_to_struct_pointer<structs::BVFlagData>(new_value);
        break;

    default:
        break;
    }
}

void change_variable_value(py::object variable, py::object new_value)
{
    auto wrapped = pyunrealsdk::type_casters::cast<unrealsdk::unreal::WrappedStruct *>(variable);

    common::BehaviorVariableData *variable_data =
        reinterpret_cast<common::BehaviorVariableData *>(wrapped->base.get());

    change_variable_value_inner(variable_data, new_value);
}

void change_variable_type(py::object variable, uint8_t variable_type)
{
    if (variable_type >= static_cast<uint8_t>(enums::EBehaviorVariableType::BVAR_MAX))
    {
        throw py::value_error("Invalid type value");
    }

    auto wrapped = pyunrealsdk::type_casters::cast<unrealsdk::unreal::WrappedStruct *>(variable);
    common::BehaviorVariableData *variable_data =
        reinterpret_cast<common::BehaviorVariableData *>(wrapped->base.get());

    variable_data->Type = static_cast<enums::EBehaviorVariableType>(variable_type);

    change_variable_value_inner(variable_data, py::none());
}
} // namespace bpd_vars