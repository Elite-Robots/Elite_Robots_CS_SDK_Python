#include "ControllerLogWrapper.hpp"
#include "DashboardClientWrapper.hpp"
#include "DataTypeWrapper.hpp"
#include "EliteDriverWrapper.hpp"
#include "LogWrapper.hpp"
#include "PrimaryPackageWrapper.hpp"
#include "PrimaryPortInterfaceWrapper.hpp"
#include "RemoteUpgradeWrapper.hpp"
#include "RobotConfPackageWrapper.hpp"
#include "RobotExceptionWrapper.hpp"
#include "RtUtilsWrapper.hpp"
#include "RtsiClientInterfaceWrapper.hpp"
#include "RtsiIOInterfaceWrapper.hpp"
#include "RtsiRecipeWrapper.hpp"
#include "VersionInfoWrapper.hpp"

#include <pybind11/pybind11.h>

namespace py = pybind11;

#ifdef _WIN32
#include <windows.h>

std::string ensureUTF8(const std::string& input) {
    // Assume the input is in ANSI local encoding (ACP). First convert it to wide characters, then convert to UTF-8.
    if (input.empty()) {
        return "";
    }

    // MultiByte -> WideChar
    int wlen = MultiByteToWideChar(CP_ACP, 0, input.c_str(), -1, nullptr, 0);
    if (wlen <= 0) {
        // fallback
        return input;
    }

    std::wstring wide(wlen, L'\0');
    MultiByteToWideChar(CP_ACP, 0, input.c_str(), -1, &wide[0], wlen);

    // WideChar -> UTF-8
    int u8len = WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (u8len <= 0) {
        // fallback
        return input;
    }

    std::string utf8(u8len, '\0');
    WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), -1, &utf8[0], u8len, nullptr, nullptr);

    // Remove the trailing '\0'
    if (!utf8.empty() && utf8.back() == '\0') {
        utf8.pop_back();
    }
    return utf8;
}

void translateException(std::exception_ptr p) {
    try {
        if (p) {
            std::rethrow_exception(p);
        }
    } catch (const std::exception& ex) {
        std::string msg = ensureUTF8(ex.what());
        PyErr_SetString(PyExc_RuntimeError, msg.c_str());
    }
}

#endif

PYBIND11_MODULE(elite_cs_sdk_python, m) {
    m.doc() = "Elite Robots CS SDK Python interface";
#ifdef _WIN32
    py::register_exception_translator(translateException);
#endif
    bindDataTypes(m);
    bindDashboardClient(m);
    bindRobotException(m);
    bindPrimaryPortInterface(m);
    bindEliteDriver(m);
    bindPrimaryPackage(m);
    bindRtsiClientInterface(m);
    bindRtsiIOInterface(m);
    bindVersionInfo(m);
    bindRtsiRecipe(m);
    bindLog(m);
    bindRemoteUpgrade(m);
    bindRobotConfPackage(m);
    bindControllerLog(m);
    bindRtUtils(m);
}
