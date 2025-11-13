// SPDX-License-Identifier: MIT
// Copyright (c) 2025, Elite Robots.
#include "SerialCommunicationWrapper.hpp"
#include <Elite/SerialCommunication.hpp>
#include <iostream>

namespace py = pybind11;
using namespace ELITE;

void bindSerialConfig(py::module_& m) {
    py::class_<SerialConfig>(m, "SerialConfig")
        .def(py::init<>())
        .def_readwrite("baud_rate", &SerialConfig::baud_rate)
        .def_readwrite("parity", &SerialConfig::parity)
        .def_readwrite("stop_bits", &SerialConfig::stop_bits);

    py::enum_<SerialConfig::BaudRate>(m.attr("SerialConfig"), "BaudRate", py::arithmetic())
        .value("BR_2400", SerialConfig::BaudRate::BR_2400)
        .value("BR_4800", SerialConfig::BaudRate::BR_4800)
        .value("BR_9600", SerialConfig::BaudRate::BR_9600)
        .value("BR_19200", SerialConfig::BaudRate::BR_19200)
        .value("BR_38400", SerialConfig::BaudRate::BR_38400)
        .value("BR_57600", SerialConfig::BaudRate::BR_57600)
        .value("BR_115200", SerialConfig::BaudRate::BR_115200)
        .value("BR_460800", SerialConfig::BaudRate::BR_460800)
        .value("BR_1000000", SerialConfig::BaudRate::BR_1000000)
        .value("BR_2000000", SerialConfig::BaudRate::BR_2000000)
        .export_values();

    py::enum_<SerialConfig::Parity>(m.attr("SerialConfig"), "Parity", py::arithmetic())
        .value("NONE", SerialConfig::Parity::NONE)
        .value("ODD", SerialConfig::Parity::ODD)
        .value("EVEN", SerialConfig::Parity::EVEN)
        .export_values();

    py::enum_<SerialConfig::StopBits>(m.attr("SerialConfig"), "StopBits", py::arithmetic())
        .value("ONE", SerialConfig::StopBits::ONE)
        .value("TWO", SerialConfig::StopBits::TWO)
        .export_values();
}

void bindSerialCommunication(pybind11::module_& m) {
    py::class_<SerialCommunication, SerialCommunicationSharedPtr>(m, "SerialCommunication")
        .def(py::init<const std::string&, int>(), py::arg("ip"), py::arg("port"),
            R"doc(
                Construct a new Serial Communication object.

                Args:
                    ip (str): The IP address of the serial communication server.
                    port (int): The port number of the serial communication server.
            )doc")
        .def("connect", &SerialCommunication::connect,
            R"doc(
                Connect to the RS485 TCP server.

                Returns:
                    bool: True if connected successfully, False otherwise.
            )doc")
        .def("disconnect", &SerialCommunication::disconnect,
            R"doc(
                Disconnect from the RS485 TCP server.
            )doc")
        .def("isConnected", &SerialCommunication::isConnected,
            R"doc(
                Check if the connection to the RS485 TCP server is established.
                Returns:
                    bool: True if connected, False otherwise.
            )doc")
        .def("write", [](SerialCommunication& sc, py::bytes& data) {
                std::string data_str = data;
                return sc.write(reinterpret_cast<const uint8_t*>(data_str.data()), static_cast<int>(data_str.size()));
            }, 
            py::arg("data"),
            R"doc(
                Write data to the RS485 TCP server.

                Args:
                    data (bytes): The data to be sent.
                Returns:
                    int: The number of bytes written.
            )doc")
        .def("read",
            [](SerialCommunication& sc, int size, int timeout_ms){
                std::vector<uint8_t> buffer(size);
                int read_len = sc.read(buffer.data(), size, timeout_ms);
                if (read_len <= 0) {
                    return py::bytes();
                } else {
                    return py::bytes(reinterpret_cast<const char*>(buffer.data()), read_len);
                }
            },
            py::arg("size"), py::arg("timeout_ms"),
            R"doc(
                Read data from the RS485 TCP server.

                Args:
                    size (int): The size of the data to be read.
                    timeout_ms (int): The read timeout in milliseconds.
                Returns:
                    bytes: The data read from the server.
            )doc");
}
