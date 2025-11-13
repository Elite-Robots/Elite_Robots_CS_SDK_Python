// SPDX-License-Identifier: MIT
// Copyright (c) 2025, Elite Robots.
#include "RtUtilsWrapper.hpp"
#include <Elite/RtUtils.hpp>
#include <thread>

#ifdef _WIN32
  #include <windows.h>
#else
  #include <pthread.h>
#endif

namespace py = pybind11;
using namespace ELITE;

std::thread::native_handle_type getCurrentThreadHandle() {
#ifdef _WIN32
    return reinterpret_cast<std::thread::native_handle_type>(GetCurrentThread());
#elif defined(__linux) || defined(linux) || defined(__linux__)
    return reinterpret_cast<std::thread::native_handle_type>(pthread_self());
#endif
}

bool setCurrentThreadFiFoScheduling(int priority) {
    auto handle = getCurrentThreadHandle();
    return RT_UTILS::setThreadFiFoScheduling(handle, priority);
}

bool bindCurrentThreadToCpus(int cpu) {
    auto handle = getCurrentThreadHandle();
    return RT_UTILS::bindThreadToCpus(handle, cpu);
}

void bindRtUtils(py::module_& m) {
    m.def("setCurrentThreadFiFoScheduling", &setCurrentThreadFiFoScheduling, py::arg("priority"),
          R"doc(
            Set current thread to FIFO scheduling and set the priority.

            Args:
                priority(int): Thread priority

            Returns:
                bool: True is success
        )doc");
    m.def("getThreadFiFoMaxPriority", &RT_UTILS::getThreadFiFoMaxPriority,
          R"doc(
            Get the maximum priority of the thread.

            Returns:
                int: The max thread priority
        )doc");
    m.def("bindCurrentThreadToCpus", &bindCurrentThreadToCpus, py::arg("cpu"),
          R"doc(
            Bind current thread to a specific CPU core to run.

            Args:
                cpu(int): core index

            Returns:
                bool: True is success
        )doc");
}