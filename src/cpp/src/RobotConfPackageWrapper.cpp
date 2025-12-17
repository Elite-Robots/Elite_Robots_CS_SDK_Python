// SPDX-License-Identifier: MIT
// Copyright (c) 2025, Elite Robots.
#include "RobotConfPackageWrapper.hpp"

#include "Elite/RobotConfPackage.hpp"

namespace py = pybind11;
using namespace ELITE;



void bindRobotConfPackage(pybind11::module_& m) {
    py::class_<KinematicsInfo, PrimaryPackage, std::shared_ptr<KinematicsInfo>>(m, "KinematicsInfo")
        .def(py::init<>())
        .def_readonly("dh_a_", &KinematicsInfo::dh_a_, "DH A")
        .def_readonly("dh_d_", &KinematicsInfo::dh_d_, "DH D")
        .def_readonly("dh_alpha_", &KinematicsInfo::dh_alpha_, "DH Alpha");
}
