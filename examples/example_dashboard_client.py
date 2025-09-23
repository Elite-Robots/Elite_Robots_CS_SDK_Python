#!/usr/bin/env python3
"""
Example script for using the elite_cs_sdk DashboardClientInterface.

Usage:
    python example_dashboard_client.py --ip 192.168.0.58
"""

import argparse
import sys
import elite_cs_sdk as cs

def main():
    parser = argparse.ArgumentParser(
        description="Connect to a robot's dashboard server and perform basic operations."
    )
    parser.add_argument(
        "--ip",
        required=True,
        help="IP address of the robot's dashboard server"
    )
    parser.add_argument(
        "--port",
        type=int,
        default=29999,
        help="Port number of the dashboard server (default: 29999)"
    )
    args = parser.parse_args()

    ip, port = args.ip, args.port

    dashboard = cs.DashboardClientInterface()

    print(f"[INFO] Connecting to dashboard at {ip}:{port}...")
    dashboard.connect(ip, port)

    version = dashboard.version()
    print(f"[INFO] Dashboard version: {version}")

    new_scaling = 30  # percent
    print(f"[INFO] Setting speed scaling to {new_scaling}%...")
    dashboard.setSpeedScaling(new_scaling)

    current_scaling = dashboard.speedScaling()
    print(f"[INFO] Current speed scaling: {current_scaling}%")

    mode = dashboard.robotMode()
    safety = dashboard.safetyMode()
    print(f"[INFO] Robot mode: {mode}")
    print(f"[INFO] Safety mode: {safety}")

    print("[INFO] Displaying popup message on dashboard...")
    dashboard.popup("-s", "Hello from Python SDK!")

    print("[INFO] Powering on the robot...")
    dashboard.powerOn()

    print("[INFO] Releasing robot brakes...")
    dashboard.brakeRelease()

    print("[INFO] Powering off the robot...")
    dashboard.powerOff()

    print("[INFO] Disconnecting from dashboard...")
    dashboard.disconnect()

if __name__ == "__main__":
    try:
        main()
    except Exception as e:
        print(f"[ERROR] {e}", file=sys.stderr)
        sys.exit(1)
