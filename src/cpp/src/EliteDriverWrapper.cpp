#include "EliteDriverWrapper.hpp"
#include "Elite/EliteDriver.hpp"

namespace py = pybind11;
using namespace ELITE;

static void bindEliteDriverConfig(py::module_& m) {
    py::class_<EliteDriverConfig>(m, "EliteDriverConfig")
        .def(py::init<>())
        .def_readwrite("robot_ip", &EliteDriverConfig::robot_ip, "IP-address under which the robot is reachable.")
        .def_readwrite("script_file_path", &EliteDriverConfig::script_file_path,
                       "EliRobot template script file that should be used to generate scripts that can be run.")
        .def_readwrite("local_ip", &EliteDriverConfig::local_ip,
                       "Local IP-address that the reverse_port and trajectory_port will bound.")
        .def_readwrite("headless_mode", &EliteDriverConfig::headless_mode, "If the driver should be started in headless mode.")
        .def_readwrite("script_sender_port", &EliteDriverConfig::script_sender_port,
                       "The driver will offer an interface to receive the program's script on this port."
                       "If the robot cannot connect to this port, `External Control` will stop immediately.")
        .def_readwrite(
            "reverse_port", &EliteDriverConfig::reverse_port,
            "Port that will be opened by the driver to allow direct communication between the driver and the robot controller.")
        .def_readwrite("trajectory_port", &EliteDriverConfig::trajectory_port,
                       "Port used for sending trajectory points to the robot in case of trajectory forwarding.")
        .def_readwrite(
            "script_command_port", &EliteDriverConfig::script_command_port,
            "Port used for forwarding script commands to the robot. The script commands will be executed locally on the robot.")
        .def_readwrite("servoj_time", &EliteDriverConfig::servoj_time, "The duration of servoj motion.")
        .def_readwrite("servoj_lookahead_time", &EliteDriverConfig::servoj_lookahead_time,
                       "Time [S], range [0.03,0.2] smoothens the trajectory with this lookahead time")
        .def_readwrite("servoj_gain", &EliteDriverConfig::servoj_gain, "Servo gain.")
        .def_readwrite("stopj_acc", &EliteDriverConfig::stopj_acc, "Acceleration [rad/s^2]. The acceleration of stopj motion.")
        .def_readwrite("servoj_queue_pre_recv_size", &EliteDriverConfig::servoj_queue_pre_recv_size,
                       "When using the `writeServoj()` and the `queue_mode` parameter is true, the timeout duration for the queue "
                       "waiting for. (For detailed descriptions of the queue mode, please refer to the description of this "
                       "interface in the API documentation.)")
        .def_readwrite("servoj_queue_pre_recv_timeout", &EliteDriverConfig::servoj_queue_pre_recv_timeout,
                       "When using the `writeServoj()` and the `queue_mode` parameter is true, the timeout duration for the queue "
                       "waiting for. (For detailed descriptions of the queue mode, please refer to the description of this "
                       "interface in the API documentation.)");
}

static void bindEliteDriverClass(py::module_& m) {
    auto trajectory_restult_cb = [](EliteDriver& self, py::function py_cb) {
        auto py_cb_ptr = std::make_shared<py::function>(std::move(py_cb));
        auto cpp_cb = [py_cb_ptr](TrajectoryMotionResult result) {
            py::gil_scoped_acquire gil;
            try {
                (*py_cb_ptr)(result);
            } catch (const py::error_already_set& e) {
                py::print("Python callback raised exception:", e.what());
            }
        };
        self.setTrajectoryResultCallback(cpp_cb);
    };

    py::class_<EliteDriver>(m, "EliteDriver",
                            "This is the main class for interfacing the driver. It sets up all the necessary socket connections "
                            "and handles the data exchange with the robot.")
        .def(py::init<EliteDriverConfig>(), py::arg("config"),
             R"doc(
                Construct a new Elite Driver object

                Args:
                    config (EliteDriverConfig): Configuration class for the EliteDriver. See it's code annotation for details.
            )doc")
        .def("writeServoj", &EliteDriver::writeServoj, py::arg("pos"), py::arg("timeout_ms"), py::arg("cartesian") = false,
             py::arg("queue_mode") = false,
             R"doc(
                Write servoj() points to robot

                Args:
                    pos (list): points.
                    timeout_ms (int): The read timeout configuration for the reverse socket running in the external control script on the robot.
                    cartesian (bool): True if the point sent is cartesian, false if joint-based
                    queue_mode (bool): True if use queue mode, false if normal mode. (For detailed descriptions of the queue mode, please refer to the description of this interface in the API documentation.)
                Returns:
                    bool: True if send success
            )doc")
        .def("writeSpeedl", &EliteDriver::writeSpeedl, py::arg("vel"), py::arg("timeout_ms"),
             R"doc(
                Write speedl() velocity to robot

                Args:
                    vel (list): line velocity ([x, y, z, rx, ry, rz])
                    timeout_ms (int): The read timeout configuration for the reverse socket running in the external control script on the robot.
                Returns:
                    bool: True if send success
            )doc")
        .def("writeSpeedj", &EliteDriver::writeSpeedj, py::arg("vel"), py::arg("timeout_ms"),
             R"doc(
                Write speedj() velocity to robot

                Args:
                    vel (list): joint velocity
                    timeout_ms (int): The read timeout configuration for the reverse socket running in the external control script on the robot.
                Returns:
                    bool: True if send success
            )doc")
        .def("setTrajectoryResultCallback", trajectory_restult_cb, py::arg("cb"),
             R"doc(
                Register a callback for the robot-based trajectory execution completion.
                One mode of robot control is to forward a complete trajectory to the robot for execution.
                When the execution is done, the callback function registered here will be triggered.

                Args:
                    cb (Callable[[TrajectoryMotionResult], None]): Callback function that will be triggered in the event of finishing
            )doc")
        .def("writeTrajectoryPoint", &EliteDriver::writeTrajectoryPoint, py::arg("positions"), py::arg("time"),
             py::arg("blend_radius"), py::arg("cartesian"),
             R"doc(
                Writes a trajectory point onto the dedicated socket.

                Args:
                    action (list): Desired joint or cartesian positions
                    time (float): Time for the robot to reach this point
                    blend_radius (float): The radius to be used for blending between control points
                    cartesian (bool): True, if the point sent is cartesian, false if joint-based
                Returns:
                    bool: True if send success
            )doc")
        .def("writeTrajectoryControlAction", &EliteDriver::writeTrajectoryControlAction, py::arg("action"), py::arg("point_number"),
             py::arg("timeout_ms"),
             R"doc(
                Writes a control message in trajectory forward mode.

                Args:
                    action (TrajectoryControlAction): The action to be taken, such as starting a new trajectory
                    point_number (int): The number of points of a new trajectory to be sent
                    timeout_ms (int): The read timeout configuration for the reverse socket running in the external control script on the robot.
                Returns:
                    bool: True if send success
            )doc")
        .def("writeIdle", &EliteDriver::writeIdle, py::arg("timeout_ms"),
             R"doc(
                Write a idle signal only.
                When robot recv idle signal, robot will stop motion.

                Args:
                    timeout_ms (int): The read timeout configuration for the reverse socket running in the external control script on the robot.
                Returns:
                    bool: True if send success
            )doc")
        .def("writeFreedrive", &EliteDriver::writeFreedrive, py::arg("action"), py::arg("timeout_ms"),
             R"doc(
                Writes a freedrive mode control command to the robot

                Args:
                    action (FreedriveAction): Freedrive mode action assigned to this command, such as starting or stopping freedrive.
                    timeout_ms (int): The read timeout configuration for the reverse socket running in the external control script on the robot.
                Returns:
                    bool: True if send success
            )doc")
        .def("stopControl", &EliteDriver::stopControl, py::arg("wait_ms") = 10000,
             R"doc(
                Sends a stop command to the socket interface which will signal the program running on the robot to no longer listen for commands sent from the remote pc.

                Args:
                    wait_ms (int): Waiting for the robot to disconnect for a certain amount of time. The minimum value is 5.

                Returns:
                    bool: True if send success
            )doc")
        .def("isRobotConnected", &EliteDriver::isRobotConnected,
             R"doc(
                Is robot connect to server

                Returns:
                    bool: True if connected
            )doc")
        .def("zeroFTSensor", &EliteDriver::zeroFTSensor,
             R"doc(
                Zero (tare) the force and torque values measured by the force/torque sensor and applied to the tool TCP. The force and
                torque values are the force and torque vectors applied to the tool TCP obtained by the `get_tcp_force(True)` script
                instruction. These vectors have undergone processing such as load compensation.

                After this command is executed, the current force and torque measurement values will be saved as the force and torque
                reference values. All subsequent force and torque measurement values will be subtracted by this force and torque reference
                value (tared).

                Please note that the above - mentioned force and torque reference values will be updated when this command is executed and
                will be reset to 0 after the controller is restarted.

                Returns:
                    bool: True if send success
            )doc")
        .def("setPayload", &EliteDriver::setPayload, py::arg("mass"), py::arg("cog"),
             R"doc(
                This command is used to set the mass, center of gravity and moment of inertia of the robot payload

                Args:
                    mass (float): The mass of the payload
                    cog (list[int]): The coordinates of the center of gravity of the payload (relative to the flange frame).

                Returns:
                    bool: True if send success
            )doc")
        .def("setToolVoltage", &EliteDriver::setToolVoltage, py::arg("vol"),
             R"doc(
                Set the tool voltage

                Args:
                    vol (ToolVoltage): Tool voltage

                Returns:
                    bool: True if send success
            )doc")
        .def("startForceMode", &EliteDriver::startForceMode, py::arg("reference_frame"), py::arg("selection_vector"),
             py::arg("wrench"), py::arg("mode"), py::arg("limits"),
             R"doc(
                This command is used to enable force control mode and the robot will be controlled in the force control mode.

                Args:
                    reference_frame (list): A pose vector that defines the force reference frame relative to the base frame.
                        The format is [X,Y,Z,Rx,Ry,Rz], where X, Y, and Z represent position with the unit of m, Rx, Ry, and RZ
                        represent pose with the unit of rad which is defined by standard Euler angles.
                    selection_vector (list): a 6-dimensional vector consisting of 0 and 1 that defines the compliant axis in the force frame.
                        1 represents the axis is compliant and 0 represents the axis is non compliant.
                    wrench (list): The force/torque applied to the environment by the robot.
                        The robot moves/rotates along the compliant axis to adjust its pose to achieve the target force/torque.
                        The format is [Fx,Fy,Fz,Mx,My,Mz], where Fx, Fy, and Fz represent the force applied along the
                        compliant axis with the unit of N, Mx, My, and Mz represent the torque applied about the
                        compliant axis with the unit of Nm. This value is invalid for the non-compliant axis. Due to the
                        safety restrictions of joints, the actual applied force/torque is lower than the set one. In the
                        separate thread, the command get_tcp_force may be used to read the actual force/torque applied to the environment.
                    mode (ForceMode): The parameter for force control mode.
                    limits (list): The parameter for the speed limit. The format is [Vx,Vy,Vz,ωx,ωy,ωz],
                        where Vx, Vy, and Vz represent the maximum speed for TCP along
                        the compliant axis with the unit of m/s, ωx, ωy, and ωz represent the maximum speed for TCP
                        about the compliant axis with the unit of rad/s. This parameter is invalid for the non-compliant
                        axis whose trajectory will be as set before.
                Returns:
                    bool: True if send success
            )doc")
        .def("endForceMode", &EliteDriver::endForceMode,
             R"doc(
                This command is used to disable the force control mode. It also will be performed when the procedure ends.

                Returns:
                    bool: True if send success
            )doc")
        .def("sendScript", &EliteDriver::sendScript, py::arg("script"),
             R"doc(
                Send a custom script.

                Args:
                    script (str): Custom script
                Returns:
                    bool: True if send success
            )doc")
        .def("sendExternalControlScript", &EliteDriver::sendExternalControlScript,
             R"doc(
                Send external control script

                Returns:
                    bool: True if send success
            )doc")
        .def("getPrimaryPackage", &EliteDriver::getPrimaryPackage, py::arg("pkg"), py::arg("timeout_ms"),
             R"doc(
                Get primary port sub-package
                Args:
                    pkg (PrimaryPackage): sub-package
                    timeout_ms (int): timeout

                Returns:
                    bool: True if get success
            )doc")
        .def("primaryReconnect", &EliteDriver::primaryReconnect,
             R"doc(
                Reconnect robot primary interface

                Returns:
                    bool : True if success
            )doc");
}

void bindEliteDriver(py::module_& m) {
    bindEliteDriverConfig(m);
    bindEliteDriverClass(m);
}
