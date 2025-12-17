// SPDX-License-Identifier: MIT
// Copyright (c) 2025, Elite Robots.
#include <pybind11/pybind11.h>

#include "Elite/DataType.hpp"

namespace py = pybind11;
using namespace ELITE;

void bindDataTypes(py::module_& m) {
    py::enum_<RobotMode>(m, "RobotMode", py::arithmetic())
        .value("UNKNOWN", RobotMode::UNKNOWN)
        .value("NO_CONTROLLER", RobotMode::NO_CONTROLLER)
        .value("DISCONNECTED", RobotMode::DISCONNECTED)
        .value("CONFIRM_SAFETY", RobotMode::CONFIRM_SAFETY)
        .value("BOOTING", RobotMode::BOOTING)
        .value("POWER_OFF", RobotMode::POWER_OFF)
        .value("POWER_ON", RobotMode::POWER_ON)
        .value("IDLE", RobotMode::IDLE)
        .value("BACKDRIVE", RobotMode::BACKDRIVE)
        .value("RUNNING", RobotMode::RUNNING)
        .value("UPDATING_FIRMWARE", RobotMode::UPDATING_FIRMWARE)
        .value("WAITING_CALIBRATION", RobotMode::WAITING_CALIBRATION)
        .export_values();

    py::enum_<JointMode>(m, "JointMode", py::arithmetic())
        .value("MODE_RESET", JointMode::MODE_RESET)
        .value("MODE_SHUTTING_DOWN", JointMode::MODE_SHUTTING_DOWN)
        .value("MODE_BACKDRIVE", JointMode::MODE_BACKDRIVE)
        .value("MODE_POWER_OFF", JointMode::MODE_POWER_OFF)
        .value("MODE_READY_FOR_POWEROFF", JointMode::MODE_READY_FOR_POWEROFF)
        .value("MODE_NOT_RESPONDING", JointMode::MODE_NOT_RESPONDING)
        .value("MODE_MOTOR_INITIALISATION", JointMode::MODE_MOTOR_INITIALISATION)
        .value("MODE_BOOTING", JointMode::MODE_BOOTING)
        .value("MODE_BOOTLOADER", JointMode::MODE_BOOTLOADER)
        .value("MODE_VIOLATION", JointMode::MODE_VIOLATION)
        .value("MODE_FAULT", JointMode::MODE_FAULT)
        .value("MODE_RUNNING", JointMode::MODE_RUNNING)
        .value("MODE_IDLE", JointMode::MODE_IDLE)
        .export_values();

    py::enum_<SafetyMode>(m, "SafetyMode", py::arithmetic())
        .value("UNKNOWN", SafetyMode::UNKNOWN)
        .value("NORMAL", SafetyMode::NORMAL)
        .value("REDUCED", SafetyMode::REDUCED)
        .value("PROTECTIVE_STOP", SafetyMode::PROTECTIVE_STOP)
        .value("RECOVERY", SafetyMode::RECOVERY)
        .value("SAFEGUARD_STOP", SafetyMode::SAFEGUARD_STOP)
        .value("SYSTEM_EMERGENCY_STOP", SafetyMode::SYSTEM_EMERGENCY_STOP)
        .value("ROBOT_EMERGENCY_STOP", SafetyMode::ROBOT_EMERGENCY_STOP)
        .value("VIOLATION", SafetyMode::VIOLATION)
        .value("FAULT", SafetyMode::FAULT)
        .value("VALIDATE_JOINT_ID", SafetyMode::VALIDATE_JOINT_ID)
        .value("UNDEFINED_SAFETY_MODE", SafetyMode::UNDEFINED_SAFETY_MODE)
        .value("AUTOMATIC_MODE_SAFEGUARD_STOP", SafetyMode::AUTOMATIC_MODE_SAFEGUARD_STOP)
        .value("SYSTEM_THREE_POSITION_ENABLING_STOP", SafetyMode::SYSTEM_THREE_POSITION_ENABLING_STOP)
        .value("TP_THREE_POSITION_ENABLING_STOP", SafetyMode::TP_THREE_POSITION_ENABLING_STOP)
        .export_values();

    py::enum_<ToolMode>(m, "ToolMode", py::arithmetic())
        .value("UNKNOWN", ToolMode::MODE_RESET)
        .value("MODE_SHUTTING_DOWN", ToolMode::MODE_SHUTTING_DOWN)
        .value("MODE_POWER_OFF", ToolMode::MODE_POWER_OFF)
        .value("MODE_NOT_RESPONDING", ToolMode::MODE_NOT_RESPONDING)
        .value("MODE_BOOTING", ToolMode::MODE_BOOTING)
        .value("MODE_BOOTLOADER", ToolMode::MODE_BOOTLOADER)
        .value("MODE_FAULT", ToolMode::MODE_FAULT)
        .value("MODE_RUNNING", ToolMode::MODE_RUNNING)
        .value("MODE_IDLE", ToolMode::MODE_IDLE)
        .export_values();

    py::enum_<ToolDigitalMode>(m, "ToolDigitalMode", py::arithmetic())
        .value("SINGLE_NEEDLE", ToolDigitalMode::SINGLE_NEEDLE, "All available")
        .value("DOUBLE_NEEDLE_1", ToolDigitalMode::DOUBLE_NEEDLE_1, "0 and 1 are both available")
        .value("DOUBLE_NEEDLE_2", ToolDigitalMode::DOUBLE_NEEDLE_2, "2 and 3 are both available")
        .value("TRIPLE_NEEDLE", ToolDigitalMode::TRIPLE_NEEDLE, "All not available")
        .export_values();

    py::enum_<ToolDigitalOutputMode>(m, "ToolDigitalOutputMode", py::arithmetic())
        .value("PUSH_PULL_MODE", ToolDigitalOutputMode::PUSH_PULL_MODE, "Push/pull mode")
        .value("SOURCING_PNP_MODE", ToolDigitalOutputMode::SOURCING_PNP_MODE, "PNP")
        .value("SINKING_NPN_MODE", ToolDigitalOutputMode::SINKING_NPN_MODE, "NPN")
        .export_values();

    py::enum_<ToolVoltage>(m, "ToolVoltage", py::arithmetic())
        .value("OFF", ToolVoltage::OFF)
        .value("V_12", ToolVoltage::V_12)
        .value("V_24", ToolVoltage::V_24)
        .export_values();

    py::enum_<TaskStatus>(m, "TaskStatus", py::arithmetic())
        .value("UNKNOWN", TaskStatus::UNKNOWN)
        .value("PLAYING", TaskStatus::PLAYING)
        .value("PAUSED", TaskStatus::PAUSED)
        .value("STOPPED", TaskStatus::STOPPED)
        .export_values();

    py::enum_<TrajectoryMotionResult>(m, "TrajectoryMotionResult", py::arithmetic())
        .value("SUCCESS", TrajectoryMotionResult::SUCCESS, "Successful execution")
        .value("CANCELED", TrajectoryMotionResult::CANCELED, "Canceled by user")
        .value("FAILURE", TrajectoryMotionResult::FAILURE, "Aborted due to error during execution")
        .export_values();

    py::enum_<TrajectoryControlAction>(m, "TrajectoryControlAction", py::arithmetic())
        .value("CANCEL", TrajectoryControlAction::CANCEL, "Represents command to cancel currently active trajectory.")
        .value("NOOP", TrajectoryControlAction::NOOP, "Represents no new control command.")
        .value("START", TrajectoryControlAction::START, "Represents command to start a new trajectory.")
        .export_values();

    py::enum_<ForceMode>(m, "ForceMode", py::arithmetic())
        .value("FIX", ForceMode::FIX, "The force frame is the force reference frame.")
        .value("POINT", ForceMode::POINT,
               "The Y-axis in the force frame points from the TCP"
               "origin of the robot to the origin of the force reference frame.")
        .value("MOTION", ForceMode::MOTION,
               "The X-axis in the force frame is the projection of the TCP motion direction"
               "vector in the X-Y plane belonging to the force reference frame.")
        .value("TCP", ForceMode::TCP, "The force frame is the TCP frame.")
        .export_values();

    py::enum_<FreedriveAction>(m, "FreedriveAction", py::arithmetic())
        .value("FREEDRIVE_END", FreedriveAction::FREEDRIVE_END, "Represents command to stop freedrive mode.")
        .value("FREEDRIVE_NOOP", FreedriveAction::FREEDRIVE_NOOP, "Represents keep running in freedrive mode.")
        .value("FREEDRIVE_START", FreedriveAction::FREEDRIVE_START, "Represents command to start freedrive mode.")
        .export_values();
}
