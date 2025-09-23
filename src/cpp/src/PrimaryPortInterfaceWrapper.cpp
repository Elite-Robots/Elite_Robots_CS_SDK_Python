#include <Elite/DataType.hpp>
#include <Elite/PrimaryPortInterface.hpp>

#include <pybind11/stl.h>
#include <array>
#include <cstdint>

namespace py = pybind11;
using namespace ELITE;

void bindPrimaryPortInterface(py::module_& m) {
    py::class_<PrimaryPortInterface>(m, "PrimaryClientInterface", "Robot primary port interface")
        .def(py::init<>())
        .def("connect", &PrimaryPortInterface::connect, py::arg("ip"), py::arg("port") = PrimaryPortInterface::PRIMARY_PORT,
             py::call_guard<py::gil_scoped_release>(),
             R"doc(
                    Connect to robot primary port.

                    Args:
                        ip (str): The robot ip
                        port (int): The port(30001)
                )doc")
        .def("disconnect", &PrimaryPortInterface::disconnect, py::call_guard<py::gil_scoped_release>(),
             "Disconnect socket.And wait for the background thread to finish.")
        .def("sendScript", &PrimaryPortInterface::sendScript, py::arg("script"), py::call_guard<py::gil_scoped_release>(),
             R"doc(
                    Sends a custom script program to the robot.

                    Args:
                        script (str): Script code that shall be executed by the robot.

                    Returns:
                        True if send success
                )doc")
        .def("getPackage", &PrimaryPortInterface::getPackage, py::arg("pkg"), py::arg("timeout_ms"),
             py::call_guard<py::gil_scoped_release>(),
             R"doc(
                    Get primary sub-package data.

                    Args:
                        pkg (PrimaryPackage): Primary sub-package. 

                    Returns:
                        True if get success
                )doc")
        .def("getLocalIP", &PrimaryPortInterface::getLocalIP, "Get the local IP")
        .def(
            "registerRobotExceptionCallback",
            [](PrimaryPortInterface& self, py::function py_cb) {
                auto py_cb_ptr = std::make_shared<py::function>(std::move(py_cb));
                self.registerRobotExceptionCallback([py_cb_ptr](std::shared_ptr<RobotException> ex) {
                    py::gil_scoped_acquire gil;
                    if (ex->getType() == RobotException::Type::ROBOT_ERROR) {
                        (*py_cb_ptr)((std::static_pointer_cast<RobotError>(ex)));
                    } else if (ex->getType() == RobotException::Type::SCRIPT_RUNTIME) {
                        (*py_cb_ptr)((std::static_pointer_cast<RobotRuntimeException>(ex)));
                    }
                });
            },
            R"doc(
                Registers a callback for robot exceptions.

                This function registers a callback that will be invoked whenever
                a robot exception message is received from the primary port.

                Args:
                    cb (Callable[[RobotExceptionSharedPtr]])
            )doc");
}
