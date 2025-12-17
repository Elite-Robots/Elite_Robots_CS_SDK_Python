#!/usr/bin/env python3
"""
Example script for using the elite_cs_sdk EliteDriver.

Usage:
    python example_trajectory.py --ip 192.168.0.58

**Note (Very Important):** This script will move the robot to the joint position [0, 0, 0, 0, 0, 0]. Please ensure the safety of the operating environment.
"""

import argparse
import sys
import elite_cs_sdk as cs
import concurrent.futures
import time
import os
import inspect

def get_package_installation_path(package_name):
    module = sys.modules.get(package_name)
    if module and hasattr(module, '__file__'):
        return os.path.dirname(os.path.abspath(module.__file__))
    return None

def currentFile():
    return inspect.currentframe().f_code.co_filename

def currentLine():
    return inspect.currentframe().f_back.f_lineno

class TrajectoryControl:
    def __init__(self, EliteDriverConfig : cs.EliteDriverConfig):
        self.__config = EliteDriverConfig
        self.__dashboard = cs.DashboardClientInterface()
        self.__driver = cs.EliteDriver(EliteDriverConfig)

        cs.logInfoMessage(currentFile(), currentLine(), "Connecting to the dashboard")
        if not self.__dashboard.connect(self.__config.robot_ip):
            cs.logFatalMessage(currentFile(), currentLine(), "Failed to connect to the dashboard.")
            raise "Failed to connect to the dashboard."
        cs.logInfoMessage(currentFile(), currentLine(), "Successfully connected to the dashboard")
    
    def __del__(self):
        self.__dashboard.disconnect()
        self.__driver.stopControl()

    def startControl(self) -> bool:
        cs.logInfoMessage(currentFile(), currentLine(), "Start powering on...")
        if not self.__dashboard.powerOn():
            cs.logFatalMessage(currentFile(), currentLine(), "Power-on failed")
            return False
        cs.logInfoMessage(currentFile(), currentLine(), "Power-on succeeded")

        cs.logInfoMessage(currentFile(), currentLine(), "Start releasing brake...")
        if not self.__dashboard.brakeRelease():
            cs.logFatalMessage(currentFile(), currentLine(), "Brake release failed")
            return False
        cs.logInfoMessage(currentFile(), currentLine(), "Brake released")

        if self.__config.headless_mode:
            if not self.__driver.isRobotConnected():
                if not self.__driver.sendExternalControlScript():
                    cs.logFatalMessage(currentFile(), currentLine(), "Fail to send external control script")
                    return False
        else:
            if not self.__dashboard.playProgram():
                cs.logFatalMessage(currentFile(), currentLine(), "Fail to play program")
                return False
            
        cs.logInfoMessage(currentFile(), currentLine(), "Wait external control script run...")
        while not self.__driver.isRobotConnected():
            time.sleep(0.1)
        cs.logInfoMessage(currentFile(), currentLine(), "External control script is running")        
        return True

    

    def moveTrajectory(self, target_points: list[list[float]], point_time: float, blend_radius: float, is_cartesian: bool) -> bool:
        move_done_future = concurrent.futures.Future()

        def trajectory_result_callback(result: cs.TrajectoryMotionResult):
            if not move_done_future.done():
                move_done_future.set_result(result)

        self.__driver.setTrajectoryResultCallback(trajectory_result_callback)

        cs.logInfoMessage(currentFile(), currentLine(), "Trajectory motion start")
        if not self.__driver.writeTrajectoryControlAction(cs.TrajectoryControlAction.START, len(target_points), 200):
            cs.logFatalMessage(currentFile(), currentLine(), "Failed to start trajectory motion")
            return False
        
        for joints in target_points:
            if not self.__driver.writeTrajectoryPoint(joints, point_time, blend_radius, is_cartesian):
                cs.logFatalMessage(currentFile(), currentLine(), "Failed to write trajectory point")
                return False
            # Send NOOP command to avoid timeout.
            if not self.__driver.writeTrajectoryControlAction(cs.TrajectoryControlAction.NOOP, 0, 200):
                cs.logFatalMessage(currentFile(), currentLine(), "Failed to send NOOP command")
                return False
        
        # Wait for the trajectory motion to complete, and send NOOP command to avoid timeout.
        while not move_done_future.done():
            time.sleep(0.01)
            if not self.__driver.writeTrajectoryControlAction(cs.TrajectoryControlAction.NOOP, 0, 200):
                cs.logFatalMessage(currentFile(), currentLine(), "Failed to send NOOP command")
                return False
        
        result = move_done_future.result()
        cs.logInfoMessage(currentFile(), currentLine(), f"Trajectory motion completed with result: {result}")

        if not self.__driver.writeIdle(0):
            cs.logFatalMessage(currentFile(), currentLine(), "Failed to write idle command")
            return False

        return result == cs.TrajectoryMotionResult.SUCCESS

    def moveTo(self, point: list[float], time: float, is_cartesian: bool) -> bool:
        return self.moveTrajectory([point], time, 0, is_cartesian)
    

def main():
    parser = argparse.ArgumentParser(
        description="Connect to a robot's server and perform basic operations."
    )
    parser.add_argument(
        "--ip",
        required=True,
        help="IP address of the robot's server"
    )
    parser.add_argument(
        "--local_ip",
        default="",
        help="IP address of the robot's server"
    )
    parser.add_argument(
        "--use_headless_mode",
        required=True,
        choices=["true", "false"],
        help="IP address of the robot's server"
    )
    args = parser.parse_args()

    ip, local_ip = args.ip, args.local_ip

    """
    RTSI connect
    """
    rtsi = cs.RtsiIOInterface("resource/output_recipe.txt", "resource/input_recipe.txt", 250.0)
    cs.logInfoMessage(currentFile(), currentLine(), "Connecting to the RTSI...")
    if not rtsi.connect(ip):
        cs.logFatalMessage(currentFile(), currentLine(), f"Can't connect {ip} RTSI server")
        sys.exit(1)
    cs.logInfoMessage(currentFile(), currentLine(), "Successfully connected to the RTSI")

    actual_joints = rtsi.getActualJointPositions()
    target_joints = actual_joints
    target_joints[3] = -1.57

    config = cs.EliteDriverConfig()
    config.robot_ip = ip
    config.local_ip = local_ip
    config.script_file_path = get_package_installation_path("elite_cs_sdk") + "/external_control.script"
    config.headless_mode = args.use_headless_mode.lower() == "true"

    controller = TrajectoryControl(config)

    cs.logInfoMessage(currentFile(), currentLine(), "Starting trajectory control...")
    if not controller.startControl():
        cs.logFatalMessage(currentFile(), currentLine(),"Failed to start trajectory control.")
        sys.exit(1)
    cs.logInfoMessage(currentFile(), currentLine(),"Trajectory control started")

    cs.logInfoMessage(currentFile(), currentLine(), f"Moving joints to target: [{target_joints[0]}, {target_joints[1]}, {target_joints[2]}, {target_joints[3]}, {target_joints[4]}, {target_joints[5]}]")
    if not controller.moveTo(target_joints, 3, False):
        cs.logFatalMessage(currentFile(), currentLine(), "Failed to move joints to target.");
        sys.exit(1)
    
    target_pose = rtsi.getActualTCPPose()

    target_pose[2] -= 0.2
    trajectory = [target_pose.copy()]

    target_pose[1] -= 0.2
    trajectory.append(target_pose.copy())

    target_pose[1] += 0.2
    target_pose[2] += 0.2
    trajectory.append(target_pose.copy())

    cs.logInfoMessage(currentFile(), currentLine(), "Moving joints to target")
    if not controller.moveTrajectory(trajectory, 3, 0, True):
        cs.logFatalMessage(currentFile(), currentLine(), "Failed to move trajectory.")
        sys.exit(1)
    cs.logInfoMessage(currentFile(), currentLine(), "Joints moved to target")


if __name__ == "__main__":
    try:
        main()
    except Exception as e:
        print(f"[ERROR] {e}", file=sys.stderr)
        sys.exit(1)
        