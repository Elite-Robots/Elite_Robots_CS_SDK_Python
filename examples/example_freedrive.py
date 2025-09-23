import elite_cs_sdk as cs

import argparse
import sys
import inspect
import time
import os

def get_package_installation_path(package_name):
    module = sys.modules.get(package_name)
    if module and hasattr(module, '__file__'):
        return os.path.dirname(os.path.abspath(module.__file__))
    return None

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
    is_headless_mode = args.use_headless_mode.lower() == "true"

    config = cs.EliteDriverConfig()
    config.robot_ip = ip
    config.local_ip = local_ip
    config.headless_mode = is_headless_mode
    config.script_file_path = get_package_installation_path("elite_cs_sdk") + "/external_control.script"

    driver = cs.EliteDriver(config)

    cs.logInfoMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "Waitting for robot connecting")
    while not driver.isRobotConnected():
        time.sleep(0.01)
    cs.logInfoMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "Robot connected")

    cs.logInfoMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "Start freedrive mode")
    driver.writeFreedrive(cs.FreedriveAction.FREEDRIVE_START, 100)
    try:
        while True:
            driver.writeFreedrive(cs.FreedriveAction.FREEDRIVE_NOOP, 100)
            time.sleep(0.01)
    except KeyboardInterrupt:
        cs.logInfoMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "End freedrive mode")
        driver.writeFreedrive(cs.FreedriveAction.FREEDRIVE_END, 100)
        driver.stopControl()

    
if __name__ == "__main__":
    main()
