#!/usr/bin/env python3
"""
Example script for using the elite_cs_sdk PrimaryClientInterface.

Usage:
    python example_primary_client.py --ip 192.168.0.58
"""

import argparse
import elite_cs_sdk as cs
import time
import struct
import sys


class CartesianInfoPackage(cs.PrimaryPackage):
    def __init__(self):
        super().__init__(4)

    def parser(self, data: bytes):
        vars = [
            "msg_len", "msg_type", "tcp_x", "tcp_y", "tcp_z",
            "rot_x", "rot_y", "rot_z", "offset_px", "offset_py",
            "offset_pz", "offset_rotx", "offset_roty", "offset_rotz"
        ]
        values = struct.unpack_from('>iBdddddddddddd', data)

        for name, value in zip(vars, values):
            print(f"{name}: {value}")
        
        

def exceptionCb(ex):
    print(f"Exception: {ex.getType()}")
    print(f"\ttimestamp: {ex.getTimeStamp()}")
    if isinstance(ex, cs.RobotError):
        print(f"\terror code: {ex.getErrorCode()}")
        print(f"\terror sub-code: {ex.getSubErrorCode()}")
    elif isinstance(ex, cs.RobotRuntimeException):
        print(f"\tmessage: {ex.getMessage()}")

def main():
    parser = argparse.ArgumentParser(
        description="Connect to a robot's primary port and perform basic operations."
    )
    parser.add_argument(
        "--ip",
        required=True,
        help="IP address of the robot's primary port"
    )
    parser.add_argument(
        "--port",
        type=int,
        default=30001,
        help="Port number of the Robot Primary Port (default: 30001)"
    )
    args = parser.parse_args()

    ip, port = args.ip, args.port

    pr = cs.PrimaryClientInterface()

    if pr.connect(ip, port):
        print("Success connected robot")
    else:
        print("Connect robot fail")
        exit(1)
    
    print("Wait get robot cartesian info")
    robot_conf = CartesianInfoPackage()
    pr.getPackage(robot_conf, 1000)

    kine = cs.KinematicsInfo()
    pr.getPackage(kine, 1000)
    print(f"DH A: {kine.dh_a_}")
    print(f"DH D: {kine.dh_d_}")
    print(f"DH Alpha: {kine.dh_alpha_}")

    # Register robot exception callback function
    pr.registerRobotExceptionCallback(exceptionCb)

    print("Send \"hello\" script to robot")
    pr.sendScript(b"def hello():\n\ttextmsg(\"hello world\")\nend\n")
    print("Sended \"hello\" script to robot")
    time.sleep(3)

    print("Send a script with anomalies to the robot")
    pr.sendScript(b"def func():\n\tabcd(123)\nend\n")
    print("Sended a script with anomalies to the robot")
    time.sleep(3)

    pr.disconnect()


if __name__ == "__main__":
    try:
        main()
    except Exception as e:
        print(f"[ERROR] {e}", file=sys.stderr)
        sys.exit(1)