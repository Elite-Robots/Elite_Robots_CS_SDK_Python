// SPDX-License-Identifier: MIT
// Copyright (c) 2025, Elite Robots.
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <Elite/VersionInfo.hpp>

namespace py = pybind11;
using namespace ELITE;

void bindVersionInfo(py::module_ &m) {
    py::class_<VersionInfo>(m, "VersionInfo")
        // Constructors
        .def(py::init<>(), "Create a version info with all fields set to zero.")
        .def(py::init<int, int, int, int>(), py::arg("major"), py::arg("minor"), py::arg("bugfix"), py::arg("build"),
             "Construct from individual version numbers.")
        .def(py::init<const std::string &>(), py::arg("version_str"), "Parse from a version string 'major.minor.bugfix.build'.")

        // Fields
        .def_readwrite("major", &VersionInfo::major, "Major version number.")
        .def_readwrite("minor", &VersionInfo::minor, "Minor version number.")
        .def_readwrite("bugfix", &VersionInfo::bugfix, "Bugfix version number.")
        .def_readwrite("build", &VersionInfo::build, "Build number.")

        // Methods
        .def("toString", &VersionInfo::toString, "Convert to a version string 'major.minor.bugfix.build'.")
        .def_static("fromString", &VersionInfo::fromString, py::arg("version_str"),
                    "Create VersionInfo by parsing a version string.")

        // __str__ and __repr__
        .def(
            "__str__", [](const VersionInfo &v) { return v.toString(); }, "Return the version string.")
        .def(
            "__repr__", [](const VersionInfo &v) { return "<VersionInfo " + v.toString() + ">"; },
            "Return an unambiguous representation.")

        // Comparison operators using static_cast to disambiguate overloads
        .def("__eq__", (bool(VersionInfo::*)(const VersionInfo &) const) & VersionInfo::operator==, py::arg("other"),
             "Return True if two VersionInfo objects are equal.")
        .def("__ne__", (bool(VersionInfo::*)(const VersionInfo &) const) & VersionInfo::operator!=, py::arg("other"),
             "Return True if two VersionInfo objects are not equal.")
        .def("__lt__", (bool(VersionInfo::*)(const VersionInfo &) const) & VersionInfo::operator<, py::arg("other"),
             "Return True if self < other.")
        .def("__le__", (bool(VersionInfo::*)(const VersionInfo &) const) & VersionInfo::operator<=, py::arg("other"),
             "Return True if self <= other.")
        .def("__gt__", (bool(VersionInfo::*)(const VersionInfo &) const) & VersionInfo::operator>, py::arg("other"),
             "Return True if self > other.")
        .def("__ge__", (bool(VersionInfo::*)(const VersionInfo &) const) & VersionInfo::operator>=, py::arg("other"),
             "Return True if self >= other.");

    // Expose SDK version constant
    m.attr("SDK_VERSION_INFO") = py::cast(SDK_VERSION_INFO);
}
