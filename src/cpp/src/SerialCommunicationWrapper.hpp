#pragma once

#include <pybind11/pybind11.h>

void bindSerialCommunication(pybind11::module_& m);

void bindSerialConfig(pybind11::module_& m);