#include <Elite/DataType.hpp>
#include <Elite/RtsiIOInterface.hpp>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace ELITE;

void bindRtsiIOInterface(pybind11::module_ &m) {
    py::class_<RtsiIOInterface>(m, "RtsiIOInterface")
        .def(py::init<const std::string &, const std::string &, double>(), py::arg("output_recipe_file"),
             py::arg("input_recipe_file"), py::arg("frequency"),
             R"doc(
                Construct a new Rtsi I O Interface object
                
                Args:
                    output_recipe_file: Output recipe configuration file
                    input_recipe_file: Input recipe configuration file
                    frequency: Output frequency
             )doc")
        .def(py::init<const std::vector<std::string>&, const std::vector<std::string>&, double>(), py::arg("output_recipe"),
             py::arg("input_recipe"), py::arg("frequency"),
             R"doc(
                Construct a new Rtsi I O Interface object
                
                Args:
                    output_recipe: Output recipe configuration
                    input_recipe: Input recipe configuration
                    frequency: Output frequency
             )doc"
        )
        .def("connect", &RtsiIOInterface::connect, py::arg("ip"),
             R"doc(
                Connect to RTSI server

                Args:
                    ip (str): The IP of RTSI server
                Returns:
                    bool: True if connected success, False if connected fail
             )doc")
        .def("disconnect", &RtsiIOInterface::disconnect,
             R"doc(
                Disconnect from the RTSI server.
                
                Note: This function will block until the thread finishes.
             )doc")
        .def("getControllerVersion", &RtsiIOInterface::getControllerVersion,
             R"doc(
                Get the controller version.

                Returns:
                    tuple: A tuple type where the data is, in order, major version, minor version, bugfix, and build.
             )doc")
        .def("setSpeedScaling", &RtsiIOInterface::setSpeedScaling, py::arg("scaling"),
             R"doc(
                Set the robot speed scaling.

                Args:
                    scaling (float): Speed scaling factor.
            )doc")
        .def("setStandardDigital", &RtsiIOInterface::setStandardDigital, py::arg("index"), py::arg("level"),
             R"doc(
                Set the standard digital output level.;

                Args:
                    index (int): The index of standard digital IO.
                    level (bool): High or low level.
                Returns:
                    bool: True if success, False if fail.
            )doc")
        .def("setConfigureDigital", &RtsiIOInterface::setConfigureDigital, py::arg("index"), py::arg("level"),
             R"doc(
                Set the configurable digital output level.

                Args:
                    index (int): The index of configurable digital IO.
                    level (bool): High or low level.
                Returns:
                    bool: True if success, False if fail.
            )doc")
        .def("setAnalogOutputVoltage", &RtsiIOInterface::setAnalogOutputVoltage, py::arg("index"), py::arg("value"),
             R"doc(
                Set the output voltage.

                Args:
                    index (int): The index of analog IO.
                    value (float): The voltage. Unit: V, range [0. 10]V
                Returns:
                    bool: True if success, False if fail.
            )doc")
        .def("setAnalogOutputCurrent", &RtsiIOInterface::setAnalogOutputCurrent, py::arg("index"), py::arg("value"),
             R"doc(
                Set the output current.

                Args:
                    index (int): The index of analog IO.
                    value (float): The current. Unit: A, range [0.004, 0.2]A
                Returns:
                    bool: True if success, False if fail.
            )doc")
        .def("setExternalForceTorque", &RtsiIOInterface::setExternalForceTorque, py::arg("value"),
             R"doc(
                Input external force sensor data into the system.

                Args:
                    value (vector6d_t): External force sensor data.
                Returns:
                    bool: True if success, False if fail.
            )doc")
        .def("setToolDigitalOutput", &RtsiIOInterface::setToolDigitalOutput, py::arg("index"), py::arg("level"),
             R"doc(
                Set the tool digital output level.

                Args:
                    index (int): The index of tool output IO.
                    level (bool): High or low level.
                Returns:
                    bool: True if success, False if fail.
            )doc")
        .def("getTimestamp", &RtsiIOInterface::getTimestamp,
             R"doc(
                Get the timestamp of the current data.

                Returns:
                    int: The timestamp in milliseconds.
            )doc")
        .def("getPayloadMass", &RtsiIOInterface::getPayloadMass,
             R"doc(
                Get the payload mass.

                Returns:
                    float: The payload mass in kg.
            )doc")
        .def("getPayloadCog", &RtsiIOInterface::getPayloadCog,
             R"doc(
                Get the center of gravity of the payload.

                Returns:
                    vector3d_t: Barycenter of terminal payload, unit: m
            )doc")
        .def("getScriptControlLine", &RtsiIOInterface::getScriptControlLine,
             R"doc(
                Get the script control line.

                Returns:
                    str: The line number of the running script
            )doc")
        .def("getTargetJointPositions", &RtsiIOInterface::getTargetJointPositions,
             R"doc(
                Get the target joint positions.

                Returns:
                    vector6d_t: Target joint positions. Unit is rad.
            )doc")
        .def("getTargetJointVelocity", &RtsiIOInterface::getTargetJointVelocity,
             R"doc(
                Get the target joint velocity.

                Returns:
                    vector6d_t: Target joint velocity. Unit is rad/s.
            )doc")
        .def("getActualJointPositions", &RtsiIOInterface::getActualJointPositions,
             R"doc(
                Get the actual joint positions.

                Returns:
                    vector6d_t: Actual joint positions. Unit is rad.
            )doc")
        .def("getActualJointTorques", &RtsiIOInterface::getActualJointTorques,
             R"doc(
                Get the actual joint torques.

                Returns:
                    vector6d_t: Actual joint torques. Unit is N*m.
            )doc")
        .def("getActualJointVelocity", &RtsiIOInterface::getActualJointVelocity,
             R"doc(
                Get the actual joint velocity.

                Returns:
                    vector6d_t: Actual joint velocity. Unit is rad/s.
            )doc")
        .def("getActualJointCurrent", &RtsiIOInterface::getActualJointCurrent,
             R"doc(
                Get the actual joint current.

                Returns:
                    vector6d_t: Actual joint current. Unit is A.
            )doc")
        .def("getActualJointTemperatures", &RtsiIOInterface::getActualJointTemperatures,
             R"doc(
                Get the actual joint temperatures.

                Returns:
                    vector6d_t: Actual joint temperatures. Unit is Celsius degrees.
            )doc")
        .def("getAcutalTCPPose", &RtsiIOInterface::getAcutalTCPPose,
             R"doc(
                Get the actual TCP pose.

                Returns:
                    vector6d_t: Actual TCP pose. Unit is [m, m, m, rad, rad, rad].
            )doc")
        .def("getAcutalTCPVelocity", &RtsiIOInterface::getAcutalTCPVelocity,
             R"doc(
                Get the actual TCP velocity.

                Returns:
                    vector6d_t: Actual TCP velocity. Unit is [m/s, m/s, m/s, rad/s, rad/s, rad/s].
            )doc")
        .def("getAcutalTCPForce", &RtsiIOInterface::getAcutalTCPForce,
             R"doc(
                Get the actual TCP force.

                Returns:
                    vector6d_t: Actual TCP force. Unit is [N, N, N, Nm, Nm, Nm].
            )doc")
        .def("getTargetTCPPose", &RtsiIOInterface::getTargetTCPPose,
             R"doc(
                Get the target TCP pose.

                Returns:
                    vector6d_t: Target TCP pose. Unit is [m, m, m, rad, rad, rad].
            )doc")
        .def("getTargetTCPVelocity", &RtsiIOInterface::getTargetTCPVelocity,
             R"doc(
                Get the target TCP velocity.

                Returns:
                    vector6d_t: Target TCP velocity. Unit is [m/s, m/s, m/s, rad/s, rad/s, rad/s].
            )doc")
        .def("getDigitalInputBits", &RtsiIOInterface::getDigitalInputBits,
             R"doc(
                Get the digital input bits.

                Returns:
                    uint32_t: The bit values of all digital input I/Os.
                    Note:
                        bits 0 to 15 is standard digital input
                        bits 16 to 24 is configure digital input
                        bits 24 to 28 is tool digital input
            )doc")
        .def("getDigitalOutputBits", &RtsiIOInterface::getDigitalOutputBits,
             R"doc(
                Get the digital output bits.

                Returns:
                    uint32_t: The bit values of all digital output I/Os.
                    Note:
                        bits 0 to 15 is standard digital output
                        bits 16 to 24 is configure digital output
                        bits 24 to 28 is tool digital output
            )doc")
        .def("getRobotMode", &RtsiIOInterface::getRobotMode,
             R"doc(
                Get the robot mode.

                Returns:
                    RobotMode: The robot mode.
            )doc")
        .def("getJointMode", &RtsiIOInterface::getJointMode,
             R"doc(
                Get the joint mode.

                Returns:
                    std::array<JointMode, 6>: Every joint mode.
            )doc")
        .def("getSafetyStatus", &RtsiIOInterface::getSafetyStatus,
             R"doc(
                Get the robot safety mode.

                Returns:
                    SafetyMode: The robot safety mode.
            )doc")
        .def("getActualSpeedScaling", &RtsiIOInterface::getActualSpeedScaling,
             R"doc(
                Get the actual robot speed scaling.

                Returns:
                    float: The actual robot speed scaling.
            )doc")
        .def("getTargetSpeedScaling", &RtsiIOInterface::getTargetSpeedScaling,
             R"doc(
                Get the target robot speed scaling.

                Returns:
                    float: The target robot speed scaling.
            )doc")
        .def("getRobotVoltage", &RtsiIOInterface::getRobotVoltage,
             R"doc(
                Get the robot voltage.

                Returns:
                    float: The robot voltage in V.
            )doc")
        .def("getRobotCurrent", &RtsiIOInterface::getRobotCurrent,
             R"doc(
                Get the robot current.

                Returns:
                    float: The robot current in A.
            )doc")
        .def("getRuntimeState", &RtsiIOInterface::getRuntimeState,
             R"doc(
                Get the program state.

                Returns:
                    TaskStatus: The program state.
            )doc")
        .def("getElbowPosition", &RtsiIOInterface::getElbowPosition,
             R"doc(
                Get the real-time position of the robot's elbow.

                Returns:
                    vector3d_t: The real-time position of the robot's elbow in [x, y, z].
            )doc")
        .def("getElbowVelocity", &RtsiIOInterface::getElbowVelocity,
             R"doc(
                Get the real-time velocity of the robot's elbow.

                Returns:
                    vector3d_t: The real-time velocity of the robot's elbow in [x, y, z]/s.
            )doc")
        .def("getRobotStatus", &RtsiIOInterface::getRobotStatus,
             R"doc(
                Get the robot status.

                Returns:
                    uint32_t: Robot status bits.
                    Note:
                        bits 0-3: is power on | is program running | is freedrive button pressed
            )doc")
        .def("getSafetyStatusBits", &RtsiIOInterface::getSafetyStatusBits,
             R"doc(
                Get the robot safety bits.

                Returns:
                    uint32_t: Robot safety bits.
                    Note:   Bits 0-10: is normal mode | is reduced mode | is protective stopped | is recovery mode | is safeguard stopped | is system emergency stopped | is robot emergency stopped | is emergency stopped | is violation | is fault | is stoppeddue to safety
            )doc")
        .def("getAnalogIOTypes", &RtsiIOInterface::getAnalogIOTypes,
             R"doc(
                Get the analog IO types.

                Returns:
                    uint32_t: Analog IO type bits.
                    Note:
                        Bits 0-3: analog input 0 (bit 0), analog input 1 (bit 1), analog output 0 (bit 2), analog output 1 (bit 3). 0:  current mode; 1: voltage mode
            )doc")
        .def("getAnalogInput", &RtsiIOInterface::getAnalogInput, py::arg("index"),
             R"doc(
                Get the standard analog input.

                Args:
                    index (int): The index of standard analog input: [0, 1]
                Returns:
                    float: Standard analog input [A or V]
            )doc")
        .def("getAnalogOutput", &RtsiIOInterface::getAnalogOutput, py::arg("index"),
             R"doc(
                Get the standard analog output.

                Args:
                    index (int): The index of standard analog output: [0, 1]
                Returns:
                    float: Standard analog output, unit:[A or V]
            )doc")
        .def("getIOCurrent", &RtsiIOInterface::getIOCurrent,
             R"doc(
                Get the mainboard IO current.

                Returns:
                    float: Mainboard IO current, unit: A
            )doc")
        .def("getToolMode", &RtsiIOInterface::getToolMode,
             R"doc(
                Get the tool mode.

                Returns:
                    ToolMode: Get tool mode
            )doc")
        .def("getToolAnalogInputType", &RtsiIOInterface::getToolAnalogInputType,
             R"doc(
                Get the tool analog input IO mode.

                Returns:
                    uint32_t: Tool analog input IO mode, 0: current mode, 1: voltage mode
            )doc")
        .def("getToolAnalogOutputType", &RtsiIOInterface::getToolAnalogOutputType,
             R"doc(
                Get the tool analog output IO mode.

                Returns:
                    uint32_t: Tool analog output IO mode, 0: current mode, 1: voltage mode
            )doc")
        .def("getToolAnalogInput", &RtsiIOInterface::getToolAnalogInput,
             R"doc(
                Get the tool analog input value.

                Returns:
                    float: Tool analog input value, range: current mode[0.004-0.02]A,  voltage mode[0-10]V
            )doc")
        .def("getToolAnalogOutput", &RtsiIOInterface::getToolAnalogOutput,
             R"doc(
                Get the tool analog output value.

                Returns:
                    float: Tool analog output value, range: current mode[0.004-0.02]A,  voltage mode[0-10]V
            )doc")
        .def("getToolOutputVoltage", &RtsiIOInterface::getToolOutputVoltage,
             R"doc(
                Get the tool voltage value.

                Returns:
                    float: Tool voltage value, unit: V
            )doc")
        .def("getToolOutputCurrent", &RtsiIOInterface::getToolOutputCurrent,
             R"doc(
                Get the tool current value.

                Returns:
                    float: Tool current value, unit: A
            )doc")
        .def("getToolOutputTemperature", &RtsiIOInterface::getToolOutputTemperature,
             R"doc(
                Get the tool temperature value.

                Returns:
                    float: Tool temperature value, unit: Celsius degrees
            )doc")
        .def("getToolDigitalMode", &RtsiIOInterface::getToolDigitalMode,
             R"doc(
                Get the tool digital mode.

                Returns:
                    ToolDigitalMode: Tool digital mode: single-needle, double-needle mode 1, double-needle mode 2, triple-needle
            )doc")
        .def("getToolDigitalOutputMode", &RtsiIOInterface::getToolDigitalOutputMode, py::arg("index"),
             R"doc(
                Get the tool digital output mode.

                Args:
                    index (int): The index of tool digital
                Returns:
                    ToolDigitalOutputMode: Tool digital output mode: push/pull, npn, pnp
            )doc")
        .def("getOutBoolRegisters0To31", &RtsiIOInterface::getOutBoolRegisters0To31,
             R"doc(
                Get the value (0~31) of the boolean output register.

                Returns:
                    uint32_t: Output the value (0~31) of the boolean register.
            )doc")
        .def("getOutBoolRegisters32To63", &RtsiIOInterface::getOutBoolRegisters32To63,
             R"doc(
                Get the value (32~63) of the boolean output register.

                Returns:
                    uint32_t: Output the value (32~63) of the boolean register.
            )doc")
        .def("getInBoolRegisters0To31", &RtsiIOInterface::getInBoolRegisters0To31,
             R"doc(
                Get the value (0~31) of the boolean input register.

                Returns:
                    uint32_t: Input the value (0~31) of the boolean register.
            )doc")
        .def("getInBoolRegisters32To63", &RtsiIOInterface::getInBoolRegisters32To63,
             R"doc(
                Get the value (32~63) of the boolean input register.

                Returns:
                    uint32_t: Input the value (32~63) of the boolean register.
            )doc")
        .def("getInBoolRegister", &RtsiIOInterface::getInBoolRegister, py::arg("index"),
             R"doc(
                Get the value of a specific boolean input register.

                Args:
                    index (int): The index of bool registers, range: [64, 127]
                Returns:
                    bool: Input bool register value
            )doc")
        .def("getOutBoolRegister", &RtsiIOInterface::getOutBoolRegister, py::arg("index"),
             R"doc(
                Get the value of a specific boolean output register.

                Args:
                    index (int): The index of bool registers
                Returns:
                    bool: Output bool register value
            )doc")
        .def("getInIntRegister", &RtsiIOInterface::getInIntRegister, py::arg("index"),
             R"doc(
                Get the value of a specific integer input register.

                Args:
                    index (int): The index of int registers
                Returns:
                    int: Input int register value
            )doc")
        .def("getOutIntRegister", &RtsiIOInterface::getOutIntRegister, py::arg("index"),
             R"doc(
                Get the value of a specific integer output register.

                Args:
                    index (int): The index of int registers
                Returns:
                    int: Output int register value
            )doc")
        .def("getInDoubleRegister", &RtsiIOInterface::getInDoubleRegister, py::arg("index"),
             R"doc(
                Get the value of a specific double input register.

                Args:
                    index (int): The index of int registers
                Returns:
                    double: Input double register value
            )doc")
        .def("getOutDoubleRegister", &RtsiIOInterface::getOutDoubleRegister, py::arg("index"),
             R"doc(
                Get the value of a specific double output register.

                Args:
                    index (int): The index of int registers
                Returns:
                    double: Output double register value
            )doc")
        .def(
            "getRecipeValue",
            [](RtsiIOInterface &self, const std::string &name) {
                // bool
                try {
                    bool v;
                    if (self.getRecipeValue<bool>(name, v)) {
                        return py::object(py::bool_(v));
                    }
                } catch (const std::bad_variant_access &) { /* ignore */
                }

                // int8_t
                try {
                    int8_t v;
                    if (self.getRecipeValue<int8_t>(name, v)) {
                        return py::object(py::int_(v));
                    }
                } catch (const std::bad_variant_access &) { /* ignore */
                }

                // uint8_t
                try {
                    uint8_t v;
                    if (self.getRecipeValue<uint8_t>(name, v)) {
                        return py::object(py::int_(v));
                    }
                } catch (const std::bad_variant_access &) { /* ignore */
                }

                // int16_t
                try {
                    int16_t v;
                    if (self.getRecipeValue<int16_t>(name, v)) {
                        return py::object(py::int_(v));
                    }
                } catch (const std::bad_variant_access &) { /* ignore */
                }

                // uint16_t
                try {
                    uint16_t v;
                    if (self.getRecipeValue<uint16_t>(name, v)) {
                        return py::object(py::int_(v));
                    }
                } catch (const std::bad_variant_access &) { /* ignore */
                }

                // int32
                try {
                    int32_t v;
                    if (self.getRecipeValue<int32_t>(name, v)) {
                        return py::object(py::int_(v));
                    }
                } catch (const std::bad_variant_access &) { /* ignore */
                }

                // uint32
                try {
                    uint32_t v;
                    if (self.getRecipeValue<uint32_t>(name, v)) {
                        return py::object(py::int_(v));
                    }
                } catch (const std::bad_variant_access &) { /* ignore */
                }

                // double
                try {
                    double v;
                    if (self.getRecipeValue<double>(name, v)) {
                        return py::object(py::float_(v));
                    }
                } catch (const std::bad_variant_access &) { /* ignore */
                }

                // vector3d_t
                try {
                    vector3d_t v;
                    if (self.getRecipeValue<vector3d_t>(name, v)) {
                        return py::cast(std::vector<double>{v[0], v[1], v[2]});
                    }
                } catch (const std::bad_variant_access &) { /* ignore */
                }

                // vector6d_t
                try {
                    vector6d_t v;
                    if (self.getRecipeValue<vector6d_t>(name, v)) {
                        return py::cast(std::vector<double>{v[0], v[1], v[2], v[3], v[4], v[5]});
                    }
                } catch (const std::bad_variant_access &) { /* ignore */
                }

                // vector6int32_t
                try {
                    vector6int32_t v;
                    if (self.getRecipeValue<vector6int32_t>(name, v)) {
                        return py::cast(std::vector<int32_t>{v[0], v[1], v[2], v[3], v[4], v[5]});
                    }
                } catch (const std::bad_variant_access &) { /* ignore */
                }

                // vector6uint32_t
                try {
                    vector6uint32_t v;
                    if (self.getRecipeValue<vector6uint32_t>(name, v)) {
                        return py::cast(std::vector<uint32_t>{v[0], v[1], v[2], v[3], v[4], v[5]});
                    }
                } catch (const std::bad_variant_access &) { /* ignore */
                }

                // int64
                try {
                    int64_t v;
                    if (self.getRecipeValue<int64_t>(name, v)) {
                        return py::object(py::int_(v));
                    }
                } catch (const std::bad_variant_access &) { /* ignore */
                }

                // uint64
                try {
                    uint64_t v;
                    if (self.getRecipeValue<uint64_t>(name, v)) {
                        return py::object(py::int_(v));
                    }
                } catch (const std::bad_variant_access &) { /* ignore */
                }

                // If no match, throw an error
                throw std::runtime_error("Variable '" + name + "' not found or unsupported type");
            },
            py::arg("name"))
        .def(
            "getRecipeValue",
            [](RtsiIOInterface &self, const std::string &name, py::object obj) {
                bool ok = false;
                if (py::isinstance<py::bool_>(obj)) {
                    ok = self.setInputRecipeValue(name, obj.cast<bool>());
                } else if (py::isinstance<py::int_>(obj)) {
                    ok = self.setInputRecipeValue(name, obj.cast<int64_t>());
                } else if (py::isinstance<py::float_>(obj)) {
                    ok = self.setInputRecipeValue<double>(name, obj.cast<double>());
                } else if (py::isinstance<py::tuple>(obj)) {
                    // Check if it's a vector3d_t or vector6d_t
                    auto tup = obj.cast<std::vector<double>>();
                    if (tup.size() == 3) {
                        vector3d_t v{tup[0], tup[1], tup[2]};
                        ok = self.setInputRecipeValue(name, v);
                    } else if (tup.size() == 6) {
                        vector6d_t v{tup[0], tup[1], tup[2], tup[3], tup[4], tup[5]};
                        ok = self.setInputRecipeValue(name, v);
                    }
                }
                if (!ok) {
                    throw std::runtime_error("Cannot convert Python object to any supported RTSI type");
                }
            },
            py::arg("name"), py::arg("value"),
            R"doc(
                Get the value of a variable by name.

                Args:
                    name (str): The name of the variable.
                    value: The value to set.
                Returns:
                    object: The value of the variable.
            )doc");
}