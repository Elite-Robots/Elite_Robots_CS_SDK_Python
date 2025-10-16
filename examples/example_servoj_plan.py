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

class TrapezoidalPoint:
    def __init__(self, t, pos, vel, acc):
        self.t = t
        self.pos = pos
        self.vel = vel
        self.acc = acc


def trapezoidalSpeedPlan(start: float, end: float, vmax: float, amax: float, dt: float) -> list[TrapezoidalPoint] :
    trajectory = list()

    # total displacement
    dq = end - start
    dir = 1.0 if dq >= 0 else -1.0
    dq = math.fabs(dq)

    # the time required for acceleration and deceleration
    t_acc = vmax / amax
    d_acc = 0.5 * amax * t_acc * t_acc

    t_flat = 0.0
    if dq < (2 * d_acc):
        # Fail to reach the maximum speed; switch to a triangular speed curve.
        t_acc = math.sqrt(dq / amax)
        d_acc = 0.5 * amax * t_acc * t_acc
        t_flat = 0.0
    else:
        t_flat = (dq - 2 * d_acc) / vmax
    

    # Total time
    total_time = 2 * t_acc + t_flat
    
    for t in np.arange(0, total_time, dt):
        acc = 0
        vel = 0
        pos = 0

        if (t < t_acc):
            # acc
            acc = dir * amax
            vel = acc * t
            pos = start + dir * (0.5 * amax * t * t)
        elif t < (t_acc + t_flat):
            # constant
            acc = 0.0
            vel = dir * vmax
            pos = start + dir * (d_acc + vmax * (t - t_acc))
        elif (t <= total_time) :
            # dec
            td = t - (t_acc + t_flat)
            acc = -dir * amax
            vel = dir * vmax - amax * td * dir
            pos = end - dir * (0.5 * amax * (total_time - t) * (total_time - t))
        else:
            # finish
            acc = 0.0
            vel = 0.0
            pos = end
        

        trajectory.append(TrapezoidalPoint(t, pos, vel, acc))
    
    return trajectory
    

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
    RTSI connect
    """
    rtsi = cs.RtsiIOInterface("resource/output_recipe.txt", "resource/input_recipe.txt", 250.0)
    cs.logInfoMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "Connecting to the RTSI...")
    if not rtsi.connect(ip):
        cs.logFatalMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, f"Can't connect {ip} RTSI server")
        sys.exit(1)
    cs.logInfoMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "Successfully connected to the RTSI")

    """
    Dashboard connect and enable robot
    """
    dashboard = cs.DashboardClientInterface()
    # Connect dashboard
    cs.logInfoMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "Connecting to the dashboard...")
    if not dashboard.connect(ip):
        cs.logFatalMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "Failed to connect to the dashboard.")
        sys.exit(1)
    cs.logInfoMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "Successfully connected to the dashboard")
    
    # Power on
    cs.logInfoMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "Start powering on...")
    if not dashboard.powerOn():
        cs.logFatalMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "Power-on failed.")
        sys.exit(1)
    cs.logInfoMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "Power-on failed")

    # Brake release
    cs.logInfoMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "Start releasing brake...")
    if not dashboard.brakeRelease():
        cs.logFatalMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "Release brake fail")
        sys.exit(1)
    cs.logInfoMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "Brake released")

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
                cs.logFatalMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "Fail to send external control script")
                sys.exit(1)
    else:
        if not dashboard.playProgram():
            cs.logFatalMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "Fail to play program")
            sys.exit(1)

    cs.logInfoMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "Waitting for robot connecting")
    while not driver.isRobotConnected():
        time.sleep(0.01)
    cs.logInfoMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "External control script is running")

    # Wait 
    time.sleep(1)

    positive_rotation = False
    negative_rotation = False

    actual_joint = rtsi.getActualJointPositions()
    target_joint = actual_joint

    JOINT_FINAL_TARGET = 3.0
    
    plan_joint = list[TrapezoidalPoint]
    while not (positive_rotation and negative_rotation):
        if not positive_rotation:
            plan_joint = trapezoidalSpeedPlan(target_joint[5], JOINT_FINAL_TARGET, max_speed, max_acc, config.servoj_time)
            positive_rotation = True
        elif not negative_rotation:
            plan_joint = trapezoidalSpeedPlan(target_joint[5], -JOINT_FINAL_TARGET, max_speed, max_acc, config.servoj_time)
            negative_rotation = True

        for point in plan_joint:
            target_joint[5] = point.pos
            if not driver.writeServoj(target_joint, 100):
                cs.logFatalMessage(inspect.currentframe().f_code.co_filename, inspect.currentframe().f_lineno, "Send servoj command to robot fail")
                sys.exit(1)
            time.sleep(config.servoj_time)
            
    driver.stopControl()

    
if __name__ == "__main__":
    try:
        cs.setCurrentThreadFiFoScheduling(cs.getThreadFiFoMaxPriority())
        main()
    except Exception as e:
        print(f"[ERROR] {e}", file=sys.stderr)
        sys.exit(1)
