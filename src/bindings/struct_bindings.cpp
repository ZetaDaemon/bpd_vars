#include "struct_bindings.h"
#include "pyunrealsdk/type_casters.h"
#include "types/structs.h"
#include "unrealsdk/unreal/class_name.h"
#include "unrealsdk/unreal/classes/uenum.h"
#include "unrealsdk/unreal/classes/uobject.h"
#include "unrealsdk/unreal/classes/uscriptstruct.h"
#include "unrealsdk/unreal/wrappers/wrapped_struct.h"
#include "unrealsdk/unrealsdk.h"
#include <format>
#include <pybind11/pybind11.h>

using namespace unrealsdk::unreal;

namespace py = pybind11;

namespace bpd_vars::bindings
{

template <typename T> T *to_struct(py::object object, UScriptStruct *struct_type)
{
    auto wrapped = pyunrealsdk::type_casters::cast<WrappedStruct>(object);
    if (!wrapped.base)
    {
        throw std::runtime_error("Invalid wrapped struct");
    }
    if (wrapped.type != struct_type)
    {
        throw std::runtime_error("Expected " + struct_type->Name());
    }
    return reinterpret_cast<T *>(wrapped.base.get());
}

std::string to_string(void *value, UScriptStruct *struct_type)
{
    auto wrapped = unrealsdk::unreal::WrappedStruct(struct_type, value);
    std::string str = py::str(pyunrealsdk::type_casters::cast(&wrapped));
    return str;
}

void bind_vector(py::module_ &m)
{
    static auto struct_type =
        validate_type<UScriptStruct>(unrealsdk::find_object(L"ScriptStruct", L"Core.Object:Vector"));

    auto bound_class = py::class_<structs::BVVector>(m, "BVVector");

    bound_class.def(py::init([](py::object Value) {
                        structs::BVVector result{};
                        if (!Value.is_none())
                        {
                            result.Value = *to_struct<common::Vector>(Value, struct_type);
                        }
                        return result;
                    }),
                    py::arg("Value") = py::none());

    bound_class.def_property(
        "Value",
        [](structs::BVVector &self) { return WrappedStruct(struct_type, &self.Value); },
        [](structs::BVVector &self, py::object value) {
            /*auto wrapped = pyunrealsdk::type_casters::cast<WrappedStruct>(value);
            if (!wrapped.base)
            {
                throw std::runtime_error("Invalid wrapped struct");
            }
            if (wrapped.type != struct_type)
            {
                throw std::runtime_error("Expected Vector");
            }
            auto *vector = reinterpret_cast<common::Vector *>(wrapped.base.get());*/

            self.Value = *to_struct<common::Vector>(value, struct_type);
        });

    bound_class.def("__repr__", [](structs::BVVector &self) {
        return std::format("{{Value: {}}}", to_string(&self.Value, struct_type));
    });
}

void bind_attribute(py::module_ &m)
{
    static auto struct_type_context = validate_type<UScriptStruct>(
        unrealsdk::find_object(L"ScriptStruct", L"GearboxFramework.BehaviorProviderDefinition:SubarrayData"));

    static auto struct_type_value = validate_type<UScriptStruct>(unrealsdk::find_object(
        L"ScriptStruct", L"Engine.AttributeInitializationDefinition:AttributeInitializationData"));

    auto bound_class = py::class_<structs::BVAttributeData>(m, "BVAttributeData");

    bound_class.def(py::init([](py::object ContextVariable, py::object Value) {
                        structs::BVAttributeData result{};

                        if (!ContextVariable.is_none())
                        {
                            result.ContextVariable =
                                *to_struct<common::SubarrayData>(ContextVariable, struct_type_context);
                        }
                        if (!Value.is_none())
                        {
                            result.Value =
                                *to_struct<common::AttributeInitializationData>(Value, struct_type_value);
                        }

                        return result;
                    }),
                    py::arg("ContextVariable") = py::none(),
                    py::arg("Value") = py::none());

    bound_class.def_property(
        "ContextVariable",
        [](structs::BVAttributeData &self) {
            return WrappedStruct(struct_type_context, &self.ContextVariable);
        },
        [](structs::BVAttributeData &self, py::object value) {
            self.ContextVariable = *to_struct<common::SubarrayData>(value, struct_type_context);
        });

    bound_class.def_property(
        "Value",
        [](structs::BVAttributeData &self) { return WrappedStruct(struct_type_value, &self.Value); },
        [](structs::BVAttributeData &self, py::object value) {
            self.Value = *to_struct<common::AttributeInitializationData>(value, struct_type_value);
        });

    bound_class.def("__repr__", [](structs::BVAttributeData &self) {
        return std::format("{{Context: {}, Value: {}}}",
                           to_string(&self.ContextVariable, struct_type_context),
                           to_string(&self.Value, struct_type_value));
    });
}

void bind_direction_vector(py::module_ &m)
{
    static auto struct_type_subarray = validate_type<UScriptStruct>(
        unrealsdk::find_object(L"ScriptStruct", L"GearboxFramework.BehaviorProviderDefinition:SubarrayData"));

    static auto struct_type_vector =
        validate_type<UScriptStruct>(unrealsdk::find_object(L"ScriptStruct", L"Core.Object:Vector"));

    static auto struct_type_rotator =
        validate_type<UScriptStruct>(unrealsdk::find_object(L"ScriptStruct", L"Core.Object:Rotator"));

    auto bound_class = py::class_<structs::BVDirectionVectorData>(m, "BVDirectionVectorData");

    bound_class.def(
        py::init([](py::object Direction,
                    py::object ParentVariable,
                    py::object DefaultDirection,
                    py::object DefaultDirectionVariable,
                    py::object AdditionalRotation,
                    py::object DefaultConeAroundDirection,
                    py::object ConeVariable) {
            structs::BVDirectionVectorData result{};

            if (!Direction.is_none())
            {
                result.Direction = static_cast<enums::EDirectionRelativeToParent>(Direction.cast<uint8_t>());
            }
            if (!DefaultDirection.is_none())
            {
                result.DefaultDirection = *to_struct<common::Vector>(DefaultDirection, struct_type_vector);
            }
            if (!DefaultDirectionVariable.is_none())
            {
                result.DefaultDirectionVariable =
                    *to_struct<common::SubarrayData>(DefaultDirectionVariable, struct_type_subarray);
            }
            if (!AdditionalRotation.is_none())
            {
                result.AdditionalRotation =
                    *to_struct<common::Rotator>(AdditionalRotation, struct_type_rotator);
            }
            if (!ParentVariable.is_none())
            {
                result.ParentVariable =
                    *to_struct<common::SubarrayData>(ParentVariable, struct_type_subarray);
            }
            if (!DefaultConeAroundDirection.is_none())
            {
                result.DefaultConeAroundDirection = DefaultConeAroundDirection.cast<float>();
            }
            if (!ConeVariable.is_none())
            {
                result.ConeVariable = *to_struct<common::SubarrayData>(ConeVariable, struct_type_subarray);
            }

            return result;
        }),
        py::arg("Direction") = py::none(),
        py::arg("ParentVariable") = py::none(),
        py::arg("DefaultDirection") = py::none(),
        py::arg("DefaultDirectionVariable") = py::none(),
        py::arg("AdditionalRotation") = py::none(),
        py::arg("DefaultConeAroundDirection") = py::none(),
        py::arg("ConeVariable") = py::none());

    bound_class.def_property(
        "Direction",
        [](structs::BVDirectionVectorData &self) { return py::int_(static_cast<uint8_t>(self.Direction)); },
        [](structs::BVDirectionVectorData &self, py::object value) {
            self.Direction = static_cast<enums::EDirectionRelativeToParent>(value.cast<uint8_t>());
        });

    bound_class.def_property(
        "ParentVariable",
        [](structs::BVDirectionVectorData &self) {
            return WrappedStruct(struct_type_subarray, &self.ParentVariable);
        },
        [](structs::BVDirectionVectorData &self, py::object value) {
            self.ParentVariable = *to_struct<common::SubarrayData>(value, struct_type_subarray);
        });

    bound_class.def_property(
        "DefaultDirection",
        [](structs::BVDirectionVectorData &self) {
            return WrappedStruct(struct_type_vector, &self.DefaultDirection);
        },
        [](structs::BVDirectionVectorData &self, py::object value) {
            self.DefaultDirection = *to_struct<common::Vector>(value, struct_type_vector);
        });

    bound_class.def_property(
        "DefaultDirectionVariable",
        [](structs::BVDirectionVectorData &self) {
            return WrappedStruct(struct_type_subarray, &self.DefaultDirectionVariable);
        },
        [](structs::BVDirectionVectorData &self, py::object value) {
            self.DefaultDirectionVariable = *to_struct<common::SubarrayData>(value, struct_type_subarray);
        });

    bound_class.def_property(
        "AdditionalRotation",
        [](structs::BVDirectionVectorData &self) {
            return WrappedStruct(struct_type_rotator, &self.AdditionalRotation);
        },
        [](structs::BVDirectionVectorData &self, py::object value) {
            self.AdditionalRotation = *to_struct<common::Rotator>(value, struct_type_rotator);
        });

    bound_class.def_property(
        "DefaultConeAroundDirection",
        [](structs::BVDirectionVectorData &self) { return py::float_((self.DefaultConeAroundDirection)); },
        [](structs::BVDirectionVectorData &self, py::object value) {
            self.DefaultConeAroundDirection = value.cast<float>();
        });

    bound_class.def_property(
        "ConeVariable",
        [](structs::BVDirectionVectorData &self) {
            return WrappedStruct(struct_type_subarray, &self.ConeVariable);
        },
        [](structs::BVDirectionVectorData &self, py::object value) {
            self.ConeVariable = *to_struct<common::SubarrayData>(value, struct_type_subarray);
        });

    bound_class.def("__repr__", [](structs::BVDirectionVectorData &self) {
        return std::format(
            "{{Direction: {}, ParentVariable: {}, DefaultDirection: {}, DefaultDirectionVariable: {}, "
            "AdditionalRotation: {}, DefaultConeAroundDirection: {}, ConeVariable: {}}}",
            static_cast<uint8_t>(self.Direction),
            to_string(&self.ParentVariable, struct_type_subarray),
            to_string(&self.DefaultDirection, struct_type_vector),
            to_string(&self.DefaultDirectionVariable, struct_type_subarray),
            to_string(&self.AdditionalRotation, struct_type_rotator),
            self.DefaultConeAroundDirection,
            to_string(&self.ConeVariable, struct_type_subarray));
    });
}

void bind_attachment_location(py::module_ &m)
{
    static auto struct_type_subarray = validate_type<UScriptStruct>(
        unrealsdk::find_object(L"ScriptStruct", L"GearboxFramework.BehaviorProviderDefinition:SubarrayData"));

    static auto struct_type_vector =
        validate_type<UScriptStruct>(unrealsdk::find_object(L"ScriptStruct", L"Core.Object:Vector"));

    auto bound_class = py::class_<structs::BVAttachmentLocationData>(m, "BVAttachmentLocationData");

    bound_class.def(py::init([](py::object SourceVariable,
                                py::object AttachmentName,
                                py::object bDefaultToSourceLocation,
                                py::object DefaultLocation,
                                py::object DefaultLocationVariable) {
                        structs::BVAttachmentLocationData result{};

                        if (!SourceVariable.is_none())
                        {
                            result.SourceVariable =
                                *to_struct<common::SubarrayData>(SourceVariable, struct_type_subarray);
                        }
                        if (!AttachmentName.is_none())
                        {
                            result.AttachmentName = FName(AttachmentName.cast<std::string>());
                        }
                        if (!bDefaultToSourceLocation.is_none())
                        {
                            result.bDefaultToSourceLocation = bDefaultToSourceLocation.cast<uint32_t>();
                        }
                        if (!DefaultLocation.is_none())
                        {
                            result.DefaultLocation =
                                *to_struct<common::Vector>(DefaultLocation, struct_type_vector);
                        }
                        if (!DefaultLocationVariable.is_none())
                        {
                            result.DefaultLocationVariable = *to_struct<common::SubarrayData>(
                                DefaultLocationVariable, struct_type_subarray);
                        }

                        return result;
                    }),
                    py::arg("SourceVariable") = py::none(),
                    py::arg("AttachmentName") = py::none(),
                    py::arg("bDefaultToSourceLocation") = py::none(),
                    py::arg("DefaultLocation") = py::none(),
                    py::arg("DefaultLocationVariable") = py::none());

    bound_class.def_property(
        "SourceVariable",
        [](structs::BVAttachmentLocationData &self) {
            return WrappedStruct(struct_type_subarray, &self.SourceVariable);
        },
        [](structs::BVAttachmentLocationData &self, py::object value) {
            self.SourceVariable = *to_struct<common::SubarrayData>(value, struct_type_subarray);
        });

    bound_class.def_property(
        "AttachmentName",
        [](structs::BVAttachmentLocationData &self) { return py::str(self.AttachmentName); },
        [](structs::BVAttachmentLocationData &self, py::object value) {
            self.AttachmentName = FName(value.cast<std::string>());
        });

    bound_class.def_property(
        "bDefaultToSourceLocation",
        [](structs::BVAttachmentLocationData &self) { return py::int_(self.bDefaultToSourceLocation); },
        [](structs::BVAttachmentLocationData &self, py::object value) {
            self.bDefaultToSourceLocation = value.cast<uint32_t>();
        });

    bound_class.def_property(
        "DefaultLocation",
        [](structs::BVAttachmentLocationData &self) {
            return WrappedStruct(struct_type_vector, &self.DefaultLocation);
        },
        [](structs::BVAttachmentLocationData &self, py::object value) {
            self.DefaultLocation = *to_struct<common::Vector>(value, struct_type_vector);
        });

    bound_class.def_property(
        "DefaultLocationVariable",
        [](structs::BVAttachmentLocationData &self) {
            return WrappedStruct(struct_type_subarray, &self.DefaultLocationVariable);
        },
        [](structs::BVAttachmentLocationData &self, py::object value) {
            self.DefaultLocationVariable = *to_struct<common::SubarrayData>(value, struct_type_subarray);
        });

    bound_class.def("__repr__", [](structs::BVAttachmentLocationData &self) {
        return std::format(
            "{{SourceVariable: {}, AttachmentName: {}, bDefaultToSourceLocation: {}, DefaultLocation: {}, "
            "DefaultLocationVariable: {}}}",
            to_string(&self.SourceVariable, struct_type_subarray),
            self.AttachmentName,
            self.bDefaultToSourceLocation,
            to_string(&self.DefaultLocation, struct_type_vector),
            to_string(&self.DefaultLocationVariable, struct_type_subarray));
    });
}

void bind_instance_data(py::module_ &m)
{
    static auto struct_type_context = validate_type<UScriptStruct>(
        unrealsdk::find_object(L"ScriptStruct", L"GearboxFramework.BehaviorProviderDefinition:SubarrayData"));

    auto bound_class = py::class_<structs::BVInstanceDataData>(m, "BVInstanceDataData");

    bound_class.def(py::init([](py::object ContextVariable, py::object InstanceDataName) {
                        structs::BVInstanceDataData result{};

                        if (!ContextVariable.is_none())
                        {
                            result.ContextVariable =
                                *to_struct<common::SubarrayData>(ContextVariable, struct_type_context);
                        }
                        if (!InstanceDataName.is_none())
                        {
                            result.InstanceDataName = FName(InstanceDataName.cast<std::string>());
                        }

                        return result;
                    }),
                    py::arg("ContextVariable") = py::none(),
                    py::arg("InstanceDataName") = py::none());

    bound_class.def_property(
        "ContextVariable",
        [](structs::BVInstanceDataData &self) {
            return WrappedStruct(struct_type_context, &self.ContextVariable);
        },
        [](structs::BVInstanceDataData &self, py::object value) {
            self.ContextVariable = *to_struct<common::SubarrayData>(value, struct_type_context);
        });

    bound_class.def_property(
        "InstanceDataName",
        [](structs::BVInstanceDataData &self) { return py::str(self.InstanceDataName); },
        [](structs::BVInstanceDataData &self, py::object value) {
            self.InstanceDataName = FName(value.cast<std::string>());
        });

    bound_class.def("__repr__", [](structs::BVInstanceDataData &self) {
        return std::format("{{Context: {}, InstanceDataName: {}}}",
                           to_string(&self.ContextVariable, struct_type_context),
                           self.InstanceDataName);
    });
}

void bind_binary_math(py::module_ &m)
{
    static auto struct_type_subarray = validate_type<UScriptStruct>(
        unrealsdk::find_object(L"ScriptStruct", L"GearboxFramework.BehaviorProviderDefinition:SubarrayData"));

    auto bound_class = py::class_<structs::BVBinaryMathData>(m, "BVBinaryMathData");

    bound_class.def(
        py::init([](py::object OperandA, py::object OperandB, py::object Operation) {
            structs::BVBinaryMathData result{};

            if (!OperandA.is_none())
            {
                result.OperandA = *to_struct<common::SubarrayData>(OperandA, struct_type_subarray);
            }
            if (!OperandB.is_none())
            {
                result.OperandB = *to_struct<common::SubarrayData>(OperandB, struct_type_subarray);
            }
            if (!Operation.is_none())
            {
                result.Operation = static_cast<enums::EBinaryMathOperation>(Operation.cast<int32_t>());
            }

            return result;
        }),
        py::arg("OperandA") = py::none(),
        py::arg("OperandB") = py::none(),
        py::arg("Operation") = py::none());

    bound_class.def_property(
        "OperandA",
        [](structs::BVBinaryMathData &self) { return WrappedStruct(struct_type_subarray, &self.OperandA); },
        [](structs::BVBinaryMathData &self, py::object value) {
            self.OperandA = *to_struct<common::SubarrayData>(value, struct_type_subarray);
        });

    bound_class.def_property(
        "OperandB",
        [](structs::BVBinaryMathData &self) { return WrappedStruct(struct_type_subarray, &self.OperandB); },
        [](structs::BVBinaryMathData &self, py::object value) {
            self.OperandB = *to_struct<common::SubarrayData>(value, struct_type_subarray);
        });

    bound_class.def_property(
        "Operation",
        [](structs::BVBinaryMathData &self) { return py::int_(static_cast<int32_t>(self.Operation)); },
        [](structs::BVBinaryMathData &self, py::object value) {
            self.Operation = static_cast<enums::EBinaryMathOperation>(value.cast<int32_t>());
        });

    bound_class.def("__repr__", [](structs::BVBinaryMathData &self) {
        return std::format("{{OperandA: {}, OperandB: {}, Operation: {}}}",
                           to_string(&self.OperandA, struct_type_subarray),
                           to_string(&self.OperandB, struct_type_subarray),
                           static_cast<int32_t>(self.Operation));
    });
}

void bind_unary_math(py::module_ &m)
{
    static auto struct_type_subarray = validate_type<UScriptStruct>(
        unrealsdk::find_object(L"ScriptStruct", L"GearboxFramework.BehaviorProviderDefinition:SubarrayData"));

    auto bound_class = py::class_<structs::BVUnaryMathData>(m, "BVUnaryMathData");

    bound_class.def(py::init([](py::object Operand, py::object Operation) {
                        structs::BVUnaryMathData result{};

                        if (!Operand.is_none())
                        {
                            result.Operand = *to_struct<common::SubarrayData>(Operand, struct_type_subarray);
                        }
                        if (!Operation.is_none())
                        {
                            result.Operation = Operation.cast<int32_t>();
                        }

                        return result;
                    }),
                    py::arg("Operand") = py::none(),
                    py::arg("Operation") = py::none());

    bound_class.def_property(
        "Operand",
        [](structs::BVUnaryMathData &self) { return WrappedStruct(struct_type_subarray, &self.Operand); },
        [](structs::BVUnaryMathData &self, py::object value) {
            self.Operand = *to_struct<common::SubarrayData>(value, struct_type_subarray);
        });

    bound_class.def_property(
        "Operation",
        [](structs::BVUnaryMathData &self) { return py::int_(static_cast<int32_t>(self.Operation)); },
        [](structs::BVUnaryMathData &self, py::object value) { self.Operation = value.cast<int32_t>(); });

    bound_class.def("__repr__", [](structs::BVUnaryMathData &self) {
        return std::format(
            "{{Operand: {}, Operation: {}}}", to_string(&self.Operand, struct_type_subarray), self.Operation);
    });
}

void bind_flag(py::module_ &m)
{
    static auto struct_type_subarray = validate_type<UScriptStruct>(
        unrealsdk::find_object(L"ScriptStruct", L"GearboxFramework.BehaviorProviderDefinition:SubarrayData"));

    auto bound_class = py::class_<structs::BVFlagData>(m, "BVFlagData");

    bound_class.def(py::init([](py::object ContextVariable, py::object FlagDef) {
                        structs::BVFlagData result{};

                        if (!ContextVariable.is_none())
                        {
                            result.ContextVariable =
                                *to_struct<common::SubarrayData>(ContextVariable, struct_type_subarray);
                        }
                        if (!FlagDef.is_none())
                        {
                            result.FlagDef = pyunrealsdk::type_casters::cast<UObject *>(FlagDef);
                        }

                        return result;
                    }),
                    py::arg("ContextVariable") = py::none(),
                    py::arg("FlagDef") = py::none());

    bound_class.def_property(
        "ContextVariable",
        [](structs::BVFlagData &self) { return WrappedStruct(struct_type_subarray, &self.ContextVariable); },
        [](structs::BVFlagData &self, py::object value) {
            self.ContextVariable = *to_struct<common::SubarrayData>(value, struct_type_subarray);
        });

    bound_class.def_property(
        "FlagDef",
        [](structs::BVFlagData &self) -> py::object {
            if (self.FlagDef == nullptr)
            {
                return py::none();
            }

            return py::cast(self.FlagDef, py::return_value_policy::reference);
        },
        [](structs::BVFlagData &self, py::object value) {
            self.FlagDef = pyunrealsdk::type_casters::cast<UObject *>(value);
        });

    bound_class.def("__repr__", [](structs::BVFlagData &self) {
        std::string flag_str = py::str(pyunrealsdk::type_casters::cast(self.FlagDef));
        return std::format("{{ContextVariable: {}, FlagDef: {}}}",
                           to_string(&self.ContextVariable, struct_type_subarray),
                           flag_str);
    });
}

void bind_structs(py::module_ &m)
{
    auto structs = m.def_submodule("structs");
    bind_vector(structs);
    bind_attribute(structs);
    bind_direction_vector(structs);
    bind_attachment_location(structs);
    bind_instance_data(structs);
    bind_binary_math(structs);
    bind_unary_math(structs);
    bind_flag(structs);
}
} // namespace bpd_vars::bindings