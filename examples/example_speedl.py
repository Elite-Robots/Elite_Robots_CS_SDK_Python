import elite_cs_sdk as cs
import inspect
import os
import argparse
import sys
import math
import time
import numpy as np

def get_package_installation_path(package_name):
    module = sys.modules.get(package_name)
    if module and hasattr(module, '__file__'):
        return os.path.dirname(os.path.abspath(module.__file__))
    return None

def currentFile():
    return inspect.currentframe().f_code.co_filename

def currentLine():
    return inspect.currentframe().f_back.f_lineno

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
    parser.add_argument(
        "--max_speed",
        default = 2.0,
        help="Max joint speed rad/s"
    )
    parser.add_argument(
        "--max_acc",
        default = 2.0,
        help="Max joint acc rad/s^2"
    )
    args = parser.parse_args()

    ip, local_ip = args.ip, args.local_ip
    max_speed, max_acc = float(args.max_speed), float(args.max_acc)

    """
    Dashboard connect and enable robot
    """
    dashboard = cs.DashboardClientInterface()
    # Connect dashboard
    cs.logInfoMessage(currentFile(), currentLine(), "Connecting to the dashboard...")
    if not dashboard.connect(ip):
        cs.logFatalMessage(currentFile(), currentLine(), "Failed to connect to the dashboard.")
        sys.exit(1)
    cs.logInfoMessage(currentFile(), currentLine(), "Successfully connected to the dashboard")
    
    # Power on
    cs.logInfoMessage(currentFile(), currentLine(), "Start powering on...")
    if not dashboard.powerOn():
        cs.logFatalMessage(currentFile(), currentLine(), "Power-on failed.")
        sys.exit(1)
    cs.logInfoMessage(currentFile(), currentLine(), "Power-on failed")

    # Brake release
    cs.logInfoMessage(currentFile(), currentLine(), "Start releasing brake...")
    if not dashboard.brakeRelease():
        cs.logFatalMessage(currentFile(), currentLine(), "Release brake fail")
        sys.exit(1)
    cs.logInfoMessage(currentFile(), currentLine(), "Brake released")

    config = cs.EliteDriverConfig()
    config.robot_ip = ip
    config.local_ip = local_ip
    config.servoj_time = 0.004
    config.servoj_gain = 2000
    config.servoj_lookahead_time = 0.3
    config.script_file_path = get_package_installation_path("elite_cs_sdk") + "/external_control.script"
    config.headless_mode = args.use_headless_mode.lower() == "true"

    driver = cs.EliteDriver(config)
    # Wait 
    time.sleep(1)

    if config.headless_mode:
        if not driver.isRobotConnected():
            if not driver.sendExternalControlScript():
                cs.logFatalMessage(currentFile(), currentLine(), "Fail to send external control script")
                sys.exit(1)
    else:
        if not dashboard.playProgram():
            cs.logFatalMessage(currentFile(), currentLine(), "Fail to play program")
            sys.exit(1)

    cs.logInfoMessage(currentFile(), currentLine(), "Waitting for robot connecting")
    while not driver.isRobotConnected():
        time.sleep(0.01)
    cs.logInfoMessage(currentFile(), currentLine(), "External control script is running")

    # Wait 
    time.sleep(1)

    speedl_vector = [0, 0, -0.02, 0, 0, 0]
    driver.writeSpeedl(speedl_vector, -1)
    time.sleep(5)

    speedl_vector = [0, 0, 0.02, 0, 0, 0]
    driver.writeSpeedl(speedl_vector, -1)
    time.sleep(5)
    
    driver.stopControl()

    
if __name__ == "__main__":
    try:
        cs.setCurrentThreadFiFoScheduling(cs.getThreadFiFoMaxPriority())
        main()
    except Exception as e:
        print(f"[ERROR] {e}", file=sys.stderr)
        sys.exit(1)
