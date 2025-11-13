// SPDX-License-Identifier: MIT
// Copyright (c) 2025, Elite Robots.
#include "LogWrapper.hpp"
#include <Elite/Log.hpp>
#include <memory>
#include <string>

namespace py = pybind11;
using namespace ELITE;

// trampoline class for LogHandler
class PyLogHandler : public LogHandler {
   public:
    using LogHandler::LogHandler;

    void log(const char* file, int line, LogLevel loglevel, const char* log) override {
        PYBIND11_OVERRIDE_PURE(void, LogHandler, log, file, line, loglevel, log);
    }
};

void registerLogHandlerRaw(LogHandler* handler) {
    static std::unique_ptr<LogHandler> current_handler;
    current_handler.reset();
    current_handler.reset(handler);
    registerLogHandler(std::unique_ptr<LogHandler>(current_handler.get()));
}

void logDebugMessage(const std::string& file, int line, const std::string& msg) {
    ELITE::log(file.c_str(), line, LogLevel::ELI_DEBUG, "%s", msg.c_str());
}

void logInfoMessage(const std::string& file, int line, const std::string& msg) {
    ELITE::log(file.c_str(), line, LogLevel::ELI_INFO, "%s", msg.c_str());
}

void logWarnMessage(const std::string& file, int line, const std::string& msg) {
    ELITE::log(file.c_str(), line, LogLevel::ELI_WARN, "%s", msg.c_str());
}

void logErrorMessage(const std::string& file, int line, const std::string& msg) {
    ELITE::log(file.c_str(), line, LogLevel::ELI_ERROR, "%s", msg.c_str());
}

void logFatalMessage(const std::string& file, int line, const std::string& msg) {
    ELITE::log(file.c_str(), line, LogLevel::ELI_FATAL, "%s", msg.c_str());
}

void logNoneMessage(const std::string& file, int line, const std::string& msg) {
    ELITE::log(file.c_str(), line, LogLevel::ELI_NONE, "%s", msg.c_str());
}

void bindLog(pybind11::module_& m) {
    py::enum_<LogLevel>(m, "LogLevel")
        .value("ELI_DEBUG", LogLevel::ELI_DEBUG)
        .value("ELI_INFO", LogLevel::ELI_INFO)
        .value("ELI_WARN", LogLevel::ELI_WARN)
        .value("ELI_ERROR", LogLevel::ELI_ERROR)
        .value("ELI_FATAL", LogLevel::ELI_FATAL)
        .value("ELI_NONE", LogLevel::ELI_NONE)
        .export_values();

    py::class_<LogHandler, PyLogHandler, std::unique_ptr<LogHandler>>(
        m, "LogHandler",
        "If you want to change the way you log, "
        "you can inherit from this class and register the instance through the registerLogHandler() function")
        .def(py::init<>())
        .def("log", &LogHandler::log);

    // Config log function
    m.def("registerLogHandler", &registerLogHandlerRaw, py::arg("hanlder"),
          R"doc(
            Register a new LogHandler object for processing log messages.
                
                Args:
                    hanlder: The new log handler object
            )doc");
    m.def("unregisterLogHandler", &unregisterLogHandler, "Unregister current log handler, this will enable default log handler.");
    m.def("setLogLevel", &setLogLevel, py::arg("level"),
          R"doc(
            Set log level this will disable messages with lower log level.

            Args:
                level (LogLevel): Desired log level
        )doc");

    // Log function
    const char log_doc[] =
        R"doc(
            Log a message

            Args:
                file (str): The log message comes from this file
                line (int): The log message comes from this line
                msg (str): The log message
        )doc";
    m.def("logDebugMessage", &logDebugMessage, py::arg("file"), py::arg("line"), py::arg("msg"), log_doc);
    m.def("logInfoMessage", &logInfoMessage, py::arg("file"), py::arg("line"), py::arg("msg"), log_doc);
    m.def("logWarnMessage", &logWarnMessage, py::arg("file"), py::arg("line"), py::arg("msg"), log_doc);
    m.def("logErrorMessage", &logErrorMessage, py::arg("file"), py::arg("line"), py::arg("msg"), log_doc);
    m.def("logFatalMessage", &logFatalMessage, py::arg("file"), py::arg("line"), py::arg("msg"), log_doc);
    m.def("logNoneMessage", &logNoneMessage, py::arg("file"), py::arg("line"), py::arg("msg"), log_doc);
}