#include "variable_handler.h"
#include "pyunrealsdk/type_casters.h"
#include "types/enums.h"
#include "types/structs.h"
#include "unrealsdk/unreal/classes/uobject.h"
#include "unrealsdk/unreal/wrappers/wrapped_struct.h"
#include "unrealsdk/unrealsdk.h"
#include <pybind11/pybind11.h>

using namespace unrealsdk::unreal;

namespace bpd_vars
{
template <typename T> py::object pointer_to_pyobj(T *pntr)
{
    if (pntr == nullptr)
    {
        return py::none();
    }

    return py::cast(pntr, py::return_value_policy::reference);
}
py::object get_behavior_variable_data(py::object obj)
{
    auto wrapped = pyunrealsdk::type_casters::cast<unrealsdk::unreal::WrappedStruct>(obj);

    structs::BehaviorVariableData *variable =
        reinterpret_cast<structs::BehaviorVariableData *>(wrapped.base.get());
    switch (variable->Type)
    {
    case enums::EBehaviorVariableType::BVAR_Bool:
        return py::bool_(variable->Value.BoolValue != 0);

    case enums::EBehaviorVariableType::BVAR_Int:
        return py::int_(variable->Value.IntValue);

    case enums::EBehaviorVariableType::BVAR_Float:
        return py::float_(variable->Value.FloatValue);

    case enums::EBehaviorVariableType::BVAR_Object:
        return pointer_to_pyobj(variable->Value.ObjectValue);

    case enums::EBehaviorVariableType::BVAR_Vector:
        return pointer_to_pyobj(variable->Value.VectorValue);

    case enums::EBehaviorVariableType::BVAR_Attribute:
        return pointer_to_pyobj(variable->Value.AttributeValue);

    case enums::EBehaviorVariableType::BVAR_DirectionVector:
        return pointer_to_pyobj(variable->Value.DirectionVectorValue);

    case enums::EBehaviorVariableType::BVAR_AttachmentLocation:
        return pointer_to_pyobj(variable->Value.AttachmentLocationValue);

    case enums::EBehaviorVariableType::BVAR_InstanceData:
        return pointer_to_pyobj(variable->Value.InstanceDataValue);

    case enums::EBehaviorVariableType::BVAR_BinaryMath:
        return pointer_to_pyobj(variable->Value.BinaryMathValue);

    case enums::EBehaviorVariableType::BVAR_UnaryMath:
        return pointer_to_pyobj(variable->Value.UnaryMathValue);

    case enums::EBehaviorVariableType::BVAR_Flag:
        return pointer_to_pyobj(variable->Value.FlagValue);

    default:
        return py::none();
    }
    return py::none();
}

template <typename T> T *copy_pyobj_to_pointer(py::object obj)
{
    void *memory = unrealsdk::u_malloc<T>(sizeof(T));
    if (memory == nullptr)
    {
        throw std::bad_alloc();
    }
    if (obj.is_none())
    {
        return new (memory) T{};
    }
    return new (memory) T(*obj.cast<T *>());
}

void change_variable_value(py::object obj, py::object new_value)
{
    auto wrapped = pyunrealsdk::type_casters::cast<unrealsdk::unreal::WrappedStruct>(obj);

    structs::BehaviorVariableData *variable =
        reinterpret_cast<structs::BehaviorVariableData *>(wrapped.base.get());

    switch (variable->Type)
    {
    case enums::EBehaviorVariableType::BVAR_Bool: {
        uint32_t value = 0;
        if (!new_value.is_none())
        {
            value = new_value.cast<bool>() ? 1 : 0;
        }
        variable->Value.BoolValue = value;
        break;
    }

    case enums::EBehaviorVariableType::BVAR_Int: {
        int32_t value = 0;
        if (!new_value.is_none())
        {
            value = new_value.cast<int32_t>();
        }
        variable->Value.IntValue = value;
        break;
    }

    case enums::EBehaviorVariableType::BVAR_Float: {
        float value = 0.0f;
        if (!new_value.is_none())
        {
            value = new_value.cast<float>();
        }
        variable->Value.FloatValue = value;
        break;
    }

    case enums::EBehaviorVariableType::BVAR_Object:
        if (new_value.is_none())
        {
            variable->Value.ObjectValue = nullptr;
            break;
        }
        variable->Value.ObjectValue = pyunrealsdk::type_casters::cast<UObject *>(new_value);
        break;

    case enums::EBehaviorVariableType::BVAR_Vector:
        variable->Value.VectorValue = copy_pyobj_to_pointer<structs::BVVector>(new_value);
        break;

    case enums::EBehaviorVariableType::BVAR_Attribute:
        variable->Value.AttributeValue = copy_pyobj_to_pointer<structs::BVAttributeData>(new_value);
        break;

    case enums::EBehaviorVariableType::BVAR_DirectionVector:
        variable->Value.DirectionVectorValue =
            copy_pyobj_to_pointer<structs::BVDirectionVectorData>(new_value);
        break;

    case enums::EBehaviorVariableType::BVAR_AttachmentLocation:
        variable->Value.AttachmentLocationValue =
            copy_pyobj_to_pointer<structs::BVAttachmentLocationData>(new_value);
        break;

    case enums::EBehaviorVariableType::BVAR_InstanceData:
        variable->Value.InstanceDataValue = copy_pyobj_to_pointer<structs::BVInstanceDataData>(new_value);
        break;

    case enums::EBehaviorVariableType::BVAR_BinaryMath:
        variable->Value.BinaryMathValue = copy_pyobj_to_pointer<structs::BVBinaryMathData>(new_value);
        break;

    case enums::EBehaviorVariableType::BVAR_UnaryMath:
        variable->Value.UnaryMathValue = copy_pyobj_to_pointer<structs::BVUnaryMathData>(new_value);
        break;

    case enums::EBehaviorVariableType::BVAR_Flag:
        variable->Value.FlagValue = copy_pyobj_to_pointer<structs::BVFlagData>(new_value);
        break;

    default:
        break;
    }
}

void change_variable_type(py::object obj, uint8_t type, py::object new_value)
{
    if (type >= static_cast<uint8_t>(enums::EBehaviorVariableType::BVAR_MAX))
    {
        throw py::value_error("Invalid type value");
    }

    auto wrapped = pyunrealsdk::type_casters::cast<unrealsdk::unreal::WrappedStruct>(obj);
    structs::BehaviorVariableData *variable =
        reinterpret_cast<structs::BehaviorVariableData *>(wrapped.base.get());

    variable->Type = static_cast<enums::EBehaviorVariableType>(type);

    change_variable_value(obj, new_value);
}
} // namespace bpd_vars