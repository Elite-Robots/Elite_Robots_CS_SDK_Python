// SPDX-License-Identifier: MIT
// Copyright (c) 2025, Elite Robots.
#include "RobotExceptionWrapper.hpp"
#include "Elite/RobotException.hpp"

namespace py = pybind11;
using namespace ELITE;

void bindRobotException(py::module_& m) {
    // Robot exeception base class
    auto exception_type = py::enum_<RobotException::Type>(m, "RobotExceptionType", py::arithmetic())
                              .value("ROBOT_DISCONNECTED", RobotException::Type::ROBOT_DISCONNECTED, "Robot disconnected")
                              .value("ROBOT_ERROR", RobotException::Type::ROBOT_ERROR, "Robot hardware or system error")
                              .value("SCRIPT_RUNTIME", RobotException::Type::SCRIPT_RUNTIME, "Robot script exception");

    py::class_<RobotException, std::shared_ptr<RobotException>>(m, "RobotException")
        .def(py::init<RobotException::Type, uint64_t>())
        .def("getType", &RobotException::getType, "Get exception type")
        .def("getTimeStamp", &RobotException::getTimestamp, "Get exception timestamp");

    m.attr("RobotException").attr("Type") = exception_type;

    // Robot error class
    auto error_source = py::enum_<RobotError::Source>(m, "RobotErrorType", py::arithmetic())
                            .value("SAFETY", RobotError::Source::SAFETY)
                            .value("GUI", RobotError::Source::GUI)
                            .value("CONTROLLER", RobotError::Source::CONTROLLER)
                            .value("RTSI", RobotError::Source::RTSI)
                            .value("JOINT", RobotError::Source::JOINT)
                            .value("TOOL", RobotError::Source::TOOL)
                            .value("TP", RobotError::Source::TP)
                            .value("JOINT_FPGA", RobotError::Source::JOINT_FPGA)
                            .value("TOOL_FPGA", RobotError::Source::TOOL_FPGA);

    auto data_type = py::enum_<RobotError::DataType>(m, "RobotErrorDataType", py::arithmetic())
                         .value("NONE", RobotError::DataType::NONE)
                         .value("UNSIGNED", RobotError::DataType::UNSIGNED)
                         .value("SIGNED", RobotError::DataType::SIGNED)
                         .value("FLOAT", RobotError::DataType::FLOAT)
                         .value("HEX", RobotError::DataType::HEX)
                         .value("STRING", RobotError::DataType::STRING)
                         .value("JOINT", RobotError::DataType::JOINT);

    auto level = py::enum_<RobotError::Level>(m, "RobotErrorLevel", py::arithmetic())
                     .value("INFO", RobotError::Level::INFO)
                     .value("WARNING", RobotError::Level::WARNING)
                     .value("ERROR", RobotError::Level::ERROR)
                     .value("FATAL", RobotError::Level::FATAL);

    const char robot_error_construct_doc[] =
        R"doc(
            Construct a new Robot Error object

                Args:
                    ts (int): timestamp
                    code (int): Error code
                    sc (int): Sub-error code.
                    es (RobotError.Source): Error source module.
                    el (RobotError.Level): Error level.
                    et (RobotError.DataType): Error data type.
                    data ([string, int, float]): Additional data (e.g., string, integer, float).
        )doc";
#define ROBOT_ERROR_CONSTRUCT_PARAM                                                                                        \
    py::arg("timestamp"), py::arg("code"), py::arg("sub_code"), py::arg("source"), py::arg("level"), py::arg("data_type"), \
        py::arg("data"), robot_error_construct_doc

    py::class_<RobotError, RobotException, std::shared_ptr<RobotError>>(
        m, "RobotError",
        "Represents an error exception on the robot side, "
        "including error codes, source modules, severity level, "
        "and additional data. It describes errors at the controller or hardware level.")
        .def(py::init<uint64_t, int, int, RobotError::Source, RobotError::Level, RobotError::DataType, uint32_t>(),
             ROBOT_ERROR_CONSTRUCT_PARAM)
        .def(py::init<uint64_t, int, int, RobotError::Source, RobotError::Level, RobotError::DataType, int32_t>(),
             ROBOT_ERROR_CONSTRUCT_PARAM)
        .def(py::init<uint64_t, int, int, RobotError::Source, RobotError::Level, RobotError::DataType, float>(),
             ROBOT_ERROR_CONSTRUCT_PARAM)
        .def(py::init<uint64_t, int, int, RobotError::Source, RobotError::Level, RobotError::DataType, std::string>(),
             ROBOT_ERROR_CONSTRUCT_PARAM)
        .def("getErrorCode", &RobotError::getErrorCode, "Get the error code")
        .def("getSubErrorCode", &RobotError::getSubErrorCode, "Get the error sub-code")
        .def("getErrorSouce", &RobotError::getErrorSouce, "Get the error souce")
        .def("getErrorLevel", &RobotError::getErrorLevel, "Get the error level")
        .def("getErrorDataType", &RobotError::getErrorDataType, "Get the error data type")
        .def(
            "getData",
            [](RobotError& self) -> py::object {
                return std::visit([](auto&& arg) -> py::object { return py::cast(arg); }, self.getData());
            },
            "Get the data");

    m.attr("RobotError").attr("Source") = error_source;
    m.attr("RobotError").attr("Type") = exception_type;
    m.attr("RobotError").attr("DataType") = data_type;
    m.attr("RobotError").attr("Level") = level;

    // Robot runtime class
    py::class_<RobotRuntimeException, RobotException, std::shared_ptr<RobotRuntimeException>>(
        m, "RobotRuntimeException",
        "Represents runtime exceptions in the robot, such as syntax or execution errors in scripts. It contains line/column"
        "information and error messages.")
        .def(py::init<uint64_t, int, int, std::string&&>())
        .def("getLine", &RobotRuntimeException::getLine, "Line number of the script where the exception occurred.")
        .def("getColumn", &RobotRuntimeException::getColumn, "Column number of the script where the exception occurred.")
        .def("getMessage", &RobotRuntimeException::getMessage, "Script exception message");
}
