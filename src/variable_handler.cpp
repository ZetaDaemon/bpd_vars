#include "variable_handler.h"
#include "pyunrealsdk/type_casters.h"
#include "types/structs.h"
#include "unrealsdk/unreal/wrappers/wrapped_struct.h"
#include <pybind11/pybind11.h>

namespace bpd_vars
{
template <typename T> py::object check_pointer(T *pntr)
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
        return check_pointer(variable->Value.ObjectValue);

    case enums::EBehaviorVariableType::BVAR_Vector:
        return check_pointer(variable->Value.VectorValue);

    case enums::EBehaviorVariableType::BVAR_Attribute:
        return check_pointer(variable->Value.AttributeValue);

    case enums::EBehaviorVariableType::BVAR_DirectionVector:
        return check_pointer(variable->Value.DirectionVectorValue);

    case enums::EBehaviorVariableType::BVAR_AttachmentLocation:
        return check_pointer(variable->Value.AttachmentLocationValue);

    case enums::EBehaviorVariableType::BVAR_InstanceData:
        return check_pointer(variable->Value.InstanceDataValue);

    case enums::EBehaviorVariableType::BVAR_BinaryMath:
        return check_pointer(variable->Value.BinaryMathValue);

    case enums::EBehaviorVariableType::BVAR_UnaryMath:
        return check_pointer(variable->Value.UnaryMathValue);

    case enums::EBehaviorVariableType::BVAR_Flag:
        return check_pointer(variable->Value.FlagValue);

    default:
        return py::none();
    }
    return py::none();
}
} // namespace bpd_vars