#include <Elite/DashboardClient.hpp>
#include <Elite/DataType.hpp>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace ELITE;

void bindDashboardClient(py::module_& m) {
    py::class_<DashboardClient>(m, "DashboardClientInterface")
        .def(py::init<>())
        .def("connect", &DashboardClient::connect, py::arg("ip"), py::arg("port") = 29999,
             R"doc(
                Connect to dashboard server.
                :param ip: server IP
                :param port: server port (default 29999)
                :returns: True on success, False on failure
             )doc")
        .def("disconnect", &DashboardClient::disconnect,
             R"doc(
                Disconnect from dashboard server.
             )doc")

        .def("brakeRelease", &DashboardClient::brakeRelease, "Release brakes, returns True on success")
        .def("closeSafetyDialog", &DashboardClient::closeSafetyDialog, "Close safety dialog, returns True on success")
        .def("echo", &DashboardClient::echo, "Send echo to check connection, returns True on success")
        .def("help", &DashboardClient::help, py::arg("cmd"), "Get help string for `cmd`")
        .def("log", &DashboardClient::log, py::arg("message"), "Add a log message")
        .def("popup", &DashboardClient::popup, py::arg("arg"), py::arg("message") = "",
             R"doc(
                Popup or close message box.
                arg: '-s' to show, '-c' to close
             )doc")
        .def("quit", &DashboardClient::quit, "Quit dashboard and disconnect")
        .def("reboot", &DashboardClient::reboot, "Reboot robot and disconnect")

        .def("robotType", &DashboardClient::robotType, "Get robot type")
        .def("robotSerialNumber", &DashboardClient::robotSerialNumber, "Get robot serial number")
        .def("robotID", &DashboardClient::robotID, "Get robot ID")

        .def("powerOn", &DashboardClient::powerOn, "Power on robot")
        .def("powerOff", &DashboardClient::powerOff, "Power off robot")
        .def("shutdown", &DashboardClient::shutdown, "Shutdown robot and disconnect")

        .def("speedScaling", &DashboardClient::speedScaling, "Get speed scaling [0, 100]%)")
        .def("setSpeedScaling", &DashboardClient::setSpeedScaling, py::arg("scaling"), "Set speed scaling [0, 100]%")

        .def("robotMode", &DashboardClient::robotMode, "Get current robot mode")
        .def("safetyMode", &DashboardClient::safetyMode, "Get current safety mode")
        .def("safetySystemRestart", &DashboardClient::safetySystemRestart, "Restart safety system")
        .def("runningStatus", &DashboardClient::runningStatus, "Get current task status")
        .def("unlockProtectiveStop", &DashboardClient::unlockProtectiveStop, "Unlock protective stop")

        .def("usage", &DashboardClient::usage, py::arg("cmd"), "Get usage for dashboard command")
        .def("version", &DashboardClient::version, "Get dashboard version info")

        .def("loadConfiguration", &DashboardClient::loadConfiguration, py::arg("path"), "Load robot configuration from path")
        .def("configurationPath", &DashboardClient::configurationPath, "Get current configuration path")
        .def("isConfigurationModify", &DashboardClient::isConfigurationModify, "Check if configuration has been modified")

        .def("playProgram", &DashboardClient::playProgram, "Play loaded program")
        .def("pauseProgram", &DashboardClient::pauseProgram, "Pause running program")
        .def("stopProgram", &DashboardClient::stopProgram, "Stop running program")

        .def("getTaskPath", &DashboardClient::getTaskPath, "Get current task path")
        .def("loadTask", &DashboardClient::loadTask, py::arg("path"), "Load task from path")
        .def("getTaskStatus", &DashboardClient::getTaskStatus, "Get status of current task")
        .def("taskIsRunning", &DashboardClient::taskIsRunning, "Check if task is running")
        .def("isTaskSaved", &DashboardClient::isTaskSaved, "Check if task is saved")

        .def("sendAndReceive", &DashboardClient::sendAndReceive, py::arg("cmd"),
             "Send a raw dashboard command and receive response");
}
