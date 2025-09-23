#!/usr/bin/env python3
"""
Example script for using the elite_cs_sdk RTSI client.

Usage:
    python example_rtsi_client.py --ip 192.168.0.58 [--port 30004]
"""

import argparse
import sys
from time import sleep
import elite_cs_sdk as cs

def main():
    parser = argparse.ArgumentParser(
        description="Connect to a robot's RTSI server and exchange recipes."
    )
    parser.add_argument(
        "--ip",
        required=True,
        help="IP address of the robot's RTSI server"
    )
    parser.add_argument(
        "--port",
        type=int,
        default=30004,
        help="RTSI server port (default: 30004)"
    )
    args = parser.parse_args()

    client = cs.RtsiClientInterface()

    print(f"[INFO] Connecting to RTSI at {args.ip}:{args.port}...")
    client.connect(args.ip, args.port)

    print("[INFO] Negotiating protocol version...")
    if not client.negotiateProtocolVersion():
        print("[ERROR] Protocol negotiation failed.", file=sys.stderr)
        sys.exit(1)

    version = client.getControllerVersion()
    print(f"[INFO] Controller version: "
          f"{version.major}.{version.minor}.{version.bugfix} (build {version.build})")

    # Prepare an output recipe for variables "actual_joint_positions" "target_joint_positions" and "speed_scaling"
    variables = ["actual_joint_positions", "target_joint_positions", "target_speed_fraction"]
    frequency = 125.0
    print(f"[INFO] Setting up output recipe {variables} @ {frequency} Hz...")
    out_recipe = client.setupOutputRecipe(variables, frequency)

    # Start streaming
    print("[INFO] Starting data stream...")
    if not client.start():
        print("[ERROR] Failed to start RTSI stream.", file=sys.stderr)
        sys.exit(1)

    # Read 3 samples
    for i in range(2):
        print(f"[INFO] Waiting for sample {i+1}...")
        recipes = [out_recipe]
        count = client.receiveData(recipes, read_newest=True)
        if count >= 0 and recipes:
            sample = recipes[0]
            names  = sample.getRecipe()
            values = [sample.getValue(n) for n in names]
            rid    = sample.getID()
            print(f"[INFO] Sample {i+1} (ID={rid}):")
            for n, v in zip(names, values):
                print(f"    {n} = {v}")
        else:
            print(f"[WARN] No data received. {count}")
        sleep(1.0)

    # Pause streaming to send input
    print("[INFO] Pausing data stream...")
    client.pause()
    
    # Prepare an input recipe for "speed_slider_mask" and "speed_slider_fraction"
    in_vars = ["speed_slider_mask", "speed_slider_fraction"]
    print(f"[INFO] Setting up input recipe {in_vars}...")
    in_recipe = client.setupInputRecipe(in_vars)
    in_id = in_recipe.getID()
    print(f"[INFO] Input recipe ID: {in_id}")
    
    # Set and send the new speed fraction
    frac = 0.5
    print(f"[INFO] Sending speed_slider_fraction = {frac}")
    in_recipe.setValue("speed_slider_mask", 1)
    in_recipe.setValue("speed_slider_fraction", frac)
    client.send(in_recipe)
    
    # Optionally resume streaming to observe effect
    print("[INFO] Resuming data stream for one more sample...")
    client.start()
    recipes = [out_recipe]
    client.receiveData(recipes, read_newest=True)
    if recipes:
        sample = recipes[0]
        speed = sample.getValue("target_speed_fraction")
        print(f"[INFO] Confirmed target_speed_fraction = {speed}")
        
    print("[INFO] Pausing data stream...")
    client.pause()

    # Disconnect
    print("[INFO] Disconnecting RTSI client...")
    client.disconnect()

if __name__ == "__main__":
    try:
        main()
    except Exception as e:
        print(f"[ERROR] {e}", file=sys.stderr)
        sys.exit(1)
