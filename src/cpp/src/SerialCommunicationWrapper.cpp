// SPDX-License-Identifier: MIT
// Copyright (c) 2025, Elite Robots.
#include "SerialCommunicationWrapper.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <Elite/SerialCommunication.hpp>
#include <iostream>

namespace py = pybind11;
using namespace ELITE;

class PySerialCommunication : public SerialCommunication {
   public:
    PySerialCommunication() = default;
    ~PySerialCommunication() override = default;

    bool connect(int timeout_ms) override { PYBIND11_OVERRIDE_PURE(bool, SerialCommunication, connect, timeout_ms); }

    void disconnect() override { PYBIND11_OVERRIDE_PURE(void, SerialCommunication, disconnect, ); }

    bool isConnected() override { PYBIND11_OVERRIDE_PURE(bool, SerialCommunication, isConnected, ); }

    int getSocatPid() const override { PYBIND11_OVERRIDE_PURE(int, SerialCommunication, getSocatPid, ); }

    // write: 把 buffer 转为 py::bytes 调用 python 的 write(bytes) -> int
    int write(const uint8_t* data, size_t size) override {
        py::gil_scoped_acquire gil;
        py::object override = py::get_override(this, "write");
        if (override) {
            py::bytes b(reinterpret_cast<const char*>(data), size);
            // Python side should implement write(bytes) -> int
            return override(b).cast<int>();
        }
        // 若没有在 Python 中重载，则触发基类 pure virtual 行为（抛出）
        throw std::runtime_error("Pure virtual function 'write' not overridden in Python");
    }

    // read: 调用 python 的 read(size, timeout_ms) -> bytes/None
    int read(uint8_t* data, size_t size, int timeout_ms) override {
        py::gil_scoped_acquire gil;
        py::object override = py::get_override(this, "read");
        if (override) {
            py::object res = override(static_cast<int>(size), timeout_ms);
            if (res.is_none()) return -1;
            py::bytes b = res;
            std::string s = static_cast<std::string>(b);
            size_t copy_n = std::min(size, s.size());
            if (copy_n > 0) std::memcpy(data, s.data(), copy_n);
            return static_cast<int>(copy_n);
        }
        throw std::runtime_error("Pure virtual function 'write' not overridden in Python");
    }
};

// SerialConfig binding (保持你现有)
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
    // 注意：基类绑定要带上 trampoline 类型并且不要绑定构造函数（因为它是抽象的）
    py::class_<SerialCommunication, PySerialCommunication, std::shared_ptr<SerialCommunication>>(m, "SerialCommunication")
        .def("connect", &SerialCommunication::connect,
             R"doc(
                Connect to the RS485 TCP server.

                Returns:
                    bool: True if connected successfully, False otherwise.
            )doc")
        .def("disconnect", &SerialCommunication::disconnect, R"doc(Disconnect from the RS485 TCP server.)doc")
        .def("isConnected", &SerialCommunication::isConnected, R"doc(Check connection status.)doc")
        // write: expose as bytes -> int in Python
        .def(
            "write",
            [](SerialCommunication& sc, py::bytes data) {
                std::string s = static_cast<std::string>(data);
                return sc.write(reinterpret_cast<const uint8_t*>(s.data()), s.size());
            },
            py::arg("data"))
        // read: expose as (size:int, timeout_ms:int) -> bytes
        .def(
            "read",
            [](SerialCommunication& sc, int size, int timeout_ms) {
                if (size <= 0) {
                    return py::bytes();
                }
                std::vector<uint8_t> buf(static_cast<size_t>(size));
                int n = sc.read(buf.data(), buf.size(), timeout_ms);
                if (n <= 0) {
                    return py::bytes();
                }
                return py::bytes(reinterpret_cast<char*>(buf.data()), n);
            },
            py::arg("size"), py::arg("timeout_ms"))
        .def("getSocatPid", &SerialCommunication::getSocatPid);
}
