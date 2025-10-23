cmake_minimum_required(VERSION 3.14)

project(Elite_CS_Python_Binding)

set(PKG_BUILD_DIR "${CMAKE_BINARY_DIR}/python")
set(PKG_SRC_DIR "${CMAKE_SOURCE_DIR}/src/python")

add_subdirectory(src/cpp)

find_package(Python3 COMPONENTS Interpreter REQUIRED)

set(EXTERNAL_SCRIPT
    "${ELITE_SDK_SRC_DIR}/source/resources/external_control.script"
 )

add_custom_target(copy_python_requirements
    COMMENT "Copying .whl requirements into temporary python directory."
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_custom_command(TARGET copy_python_requirements POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${PKG_BUILD_DIR}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${PKG_BUILD_DIR}/package
        COMMAND ${CMAKE_COMMAND} -E copy ${PKG_SRC_DIR}/setup.py ${PKG_BUILD_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy ${PKG_SRC_DIR}/setup.cfg ${PKG_BUILD_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PKG_SRC_DIR}/package ${PKG_BUILD_DIR}/package

        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${PKG_BUILD_DIR}/package/elite_cs_sdk

        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${EXTERNAL_SCRIPT} ${PKG_BUILD_DIR}/package/elite_cs_sdk

        COMMAND ${CMAKE_COMMAND} -E echo "Copying all files from $<TARGET_FILE_DIR:elite_cs_sdk_python> to ${PKG_BUILD_DIR}/package/elite_cs_sdk/"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
          "$<TARGET_FILE_DIR:elite_cs_sdk_python>"
          "${PKG_BUILD_DIR}/package/elite_cs_sdk/"

        COMMAND ${CMAKE_COMMAND} -E echo "Copying all files from $<TARGET_FILE_DIR:elite-cs-series-sdk_SHARED> to ${PKG_BUILD_DIR}/package/elite_cs_sdk/"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
          "$<TARGET_FILE_DIR:elite-cs-series-sdk_SHARED>"
          "${PKG_BUILD_DIR}/package/elite_cs_sdk/"
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux" OR APPLE)
    add_custom_command(TARGET copy_python_requirements POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${PKG_BUILD_DIR}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${PKG_BUILD_DIR}/package
        COMMAND ${CMAKE_COMMAND} -E copy ${PKG_SRC_DIR}/setup.py ${PKG_BUILD_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy ${PKG_SRC_DIR}/setup.cfg ${PKG_BUILD_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PKG_SRC_DIR}/package ${PKG_BUILD_DIR}/package

        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${PKG_BUILD_DIR}/package/elite_cs_sdk

        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${EXTERNAL_SCRIPT} ${PKG_BUILD_DIR}/package/elite_cs_sdk

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:elite_cs_sdk_python>
        ${PKG_BUILD_DIR}/package/elite_cs_sdk/$<TARGET_FILE_NAME:elite_cs_sdk_python>

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:elite-cs-series-sdk_SHARED>
        ${PKG_BUILD_DIR}/package/elite_cs_sdk/$<TARGET_FILE_NAME:elite-cs-series-sdk_SHARED>
)
else()
    message(FATAL_ERROR "Unsupport operating system")
endif()


add_custom_target(python_wheel ALL
    COMMAND ${Python3_EXECUTABLE}
    -m pip wheel ${PKG_BUILD_DIR}
    --no-deps
    --use-pep517
    --wheel-dir ${CMAKE_SOURCE_DIR}/dist
    COMMENT "Building wheel from temporary python -> dist/"
    USES_TERMINAL
)

add_custom_target(generate_sdk_pyi
    COMMAND ${CMAKE_COMMAND} -E env
        PYTHONPATH=${PKG_BUILD_DIR}/package/elite_cs_sdk/
        ${Python3_EXECUTABLE} -m pybind11_stubgen elite_cs_sdk_python
        --output-dir ${PKG_BUILD_DIR}/package/elite_cs_sdk
        --ignore-invalid-expressions ELITE:: # TODO: Remove this ignore flag.

    COMMENT "Generating .pyi files using pybind11-stubgen"
    WORKING_DIRECTORY ${PKG_BUILD_DIR}
    USES_TERMINAL
)
add_dependencies(generate_sdk_pyi copy_python_requirements elite_cs_sdk_python)
add_dependencies(python_wheel copy_python_requirements elite_cs_sdk_python generate_sdk_pyi)
