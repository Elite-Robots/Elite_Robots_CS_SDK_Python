#include "ControllerLogWrapper.hpp"
#include <pybind11/functional.h>
#include "Elite/ControllerLog.hpp"

using namespace ELITE;
namespace py = pybind11;

void bindControllerLog(py::module_& m) {
    py::class_<ControllerLog>(m, "ControllerLog")
        .def(py::init<>())
        .def_static(
            "downloadSystemLog",
            [](const std::string& robot_ip,
               const std::string& password,
               const std::string& path,
               std::function<void(int, int, const char*)> cb) {
                // Note: if err == nullptr, Python will receive None
                return ControllerLog::downloadSystemLog(robot_ip, password, path, std::move(cb));
            },
            py::arg("robot_ip"),
            py::arg("password"),
            py::arg("path"),
            py::arg("progress_cb"),
            R"pbdoc(
                Download system log from the robot.

                Args:
                    robot_ip (str): Robot IP address.
                    password (str): SSH password.
                    path (str): Save path.
                    progress_cb (Callable[[f_z: int, r_z: int, err: Optional[str]]]): Download progress callback function.
                        f_z: File size.
                        r_z: Downloaded size.
                        err: Error information (None when there is no error)

                Returns:
                    bool: True if success, False otherwise.
                
                Note:
                    1. On Linux, if `libssh` is not installed, you need to ensure that the computer running the SDK has the `scp`, `ssh`,
                       and `sshpass` commands available.
                    2. In Windows, if libssh is not installed, then this interface will not be available.

            )pbdoc");
}
