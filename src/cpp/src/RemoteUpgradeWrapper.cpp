// SPDX-License-Identifier: MIT
// Copyright (c) 2025, Elite Robots.
#include "RemoteUpgradeWrapper.hpp"

#include "Elite/RemoteUpgrade.hpp"

namespace py = pybind11;


void bindRemoteUpgrade(py::module_& m) {
    m.def("upgradeControlSoftware", &ELITE::UPGRADE::upgradeControlSoftware, py::arg("ip"), py::arg("file"), py::arg("password"),
        R"doc(
            Upgrade the robot control software

            Args:
                ip (str): Robot ip
                file (str): Upgrade file
                password (str): Robot controller ssh password
            Returns:
                bool: True if success
            Notes:
                1. On Linux, if `libssh` is not installed, 
                   you need to ensure that the computer running the SDK has the `scp`, `ssh`, and `sshpass` commands available.
                2. In Windows, if libssh is not installed, then this interface will not be available.
        )doc"
    );
}