cmake_minimum_required(VERSION 3.20)

project(bpd_vars VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(
    libs/pyunrealsdk
    pyunrealsdk-build
)

pyunrealsdk_add_module(
    bpd_vars_native
    src/module.cpp
    src/variable_handler.cpp
    src/bindings/struct_bindings.cpp
)


target_include_directories(
    bpd_vars_native
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set(BPD_VARS_PYTHON_DIR
    "${PROJECT_SOURCE_DIR}/python/bpd_vars"
)

add_custom_command(
    TARGET bpd_vars_native
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
            "${BPD_VARS_PYTHON_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:bpd_vars_native>
            "${BPD_VARS_PYTHON_DIR}"
)

set(BL2_PLUGIN_DIR
    "$ENV{HOME}/.local/share/Steam/steamapps/common/Borderlands 2/Binaries/Win32/Plugins"
)

add_custom_command(
    TARGET bpd_vars_native
    POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:bpd_vars_native>
        "${BL2_PLUGIN_DIR}"

    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_BINARY_DIR}/pyunrealsdk-build/pyunrealsdk.dll"
        "${BL2_PLUGIN_DIR}"

    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_BINARY_DIR}/pyunrealsdk-build/libs/unrealsdk/unrealsdk.dll"
        "${BL2_PLUGIN_DIR}"
)