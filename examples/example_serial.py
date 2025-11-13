import elite_cs_sdk as cs

import inspect
import os
import argparse
import sys
import time

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
        "--which_serial",
        required=True,
        choices=["board", "tool"],
        help="Choose which serial."
    )
    args = parser.parse_args()

    ip, local_ip = args.ip, args.local_ip

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

    serial_config = cs.SerialConfig()
    serial_config.baud_rate = cs.SerialConfig.BaudRate.BR_115200
    serial_config.parity = cs.SerialConfig.Parity.NONE
    serial_config.stop_bits = cs.SerialConfig.StopBits.ONE

    if args.which_serial == "tool":
        serial = driver.startToolRs485(serial_config)
    elif args.which_serial == "board":
        serial = driver.startBoardRs485(serial_config)

    cs.logInfoMessage(currentFile(), currentLine(), "Connecting to serial...")
    if not serial.connect(1000):
        cs.logFatalMessage(currentFile(), currentLine(), "Failed to connect serial")
        sys.exit(1)
    cs.logInfoMessage(currentFile(), currentLine(), "Successfully connected to serial")

    cs.logInfoMessage(currentFile(), currentLine(), "Writing to serial...")
    hello_message = b'hello wrold'
    if serial.write(hello_message) <= 0:
        cs.logFatalMessage(currentFile(), currentLine(), "Failed to write to serial")
        sys.exit(1)
    cs.logInfoMessage(currentFile(), currentLine(), f"Successfully wrote to serial: {hello_message}")

    cs.logInfoMessage(currentFile(), currentLine(), "Reading from serial...")
    read_data = serial.read(64, 5000)
    cs.logInfoMessage(currentFile(), currentLine(), f"Successfully read from serial: {read_data}")

    cs.logInfoMessage(currentFile(), currentLine(), "Ending serial...")
    driver.endBoardRs485(serial)
    driver.endToolRs485(serial)
    driver.stopControl()
    cs.logInfoMessage(currentFile(), currentLine(), "Serial ended")

if __name__ == "__main__":
    main()