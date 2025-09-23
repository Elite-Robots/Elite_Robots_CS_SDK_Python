#include <Elite/DataType.hpp>
#include <Elite/RtsiClientInterface.hpp>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace ELITE;

void bindRtsiClientInterface(py::module_& m) {
    py::class_<RtsiClientInterface>(m, "RtsiClientInterface")
        .def(py::init<>())
        // Constants
        .def_readonly_static("DEFAULT_PROTOCOL_VERSION", &RtsiClientInterface::DEFAULT_PROTOCOL_VERSION,
                             "Default RTSI protocol version.")

        // Connection Management
        .def("connect", &RtsiClientInterface::connect, py::arg("ip"), py::arg("port") = 30004,
             R"doc(
Connect to the RTSI server.

Args:
    ip (str): RTSI server IP address.
    port (int, optional): RTSI server port. Defaults to 30004.
)doc")
        .def("disconnect", &RtsiClientInterface::disconnect,
             R"doc(
Disconnect from the RTSI server.
)doc")

        // Protocol Negotiation
        .def("negotiateProtocolVersion", &RtsiClientInterface::negotiateProtocolVersion,
             py::arg("version") = RtsiClientInterface::DEFAULT_PROTOCOL_VERSION,
             R"doc(
Negotiate the RTSI protocol version.

Args:
    version (int, optional): Desired protocol version. Defaults to DEFAULT_PROTOCOL_VERSION.

Returns:
    bool: True if negotiation succeeded, False otherwise.
)doc")

        // Version Info
        .def("getControllerVersion", &RtsiClientInterface::getControllerVersion,
             R"doc(
Retrieve controller version information.

Returns:
    VersionInfo: Contains major, minor, bugfix, and build numbers.
)doc")

        // Recipe Setup
        .def("setupOutputRecipe", &RtsiClientInterface::setupOutputRecipe, py::arg("recipe_list"), py::arg("frequency") = 250.0,
             R"doc(
Subscribe to output variables.

Args:
    recipe_list (List[str]): Names of variables to subscribe.
    frequency (float, optional): Update frequency in Hz. Defaults to 250.0.

Returns:
    RtsiRecipeSharedPtr: Shared pointer to the output recipe.
)doc")
        .def("setupInputRecipe", &RtsiClientInterface::setupInputRecipe, py::arg("recipe"),
             R"doc(
Subscribe to input variables.

Args:
    recipe (List[str]): Names of variables to subscribe.

Returns:
    RtsiRecipeSharedPtr: Shared pointer to the input recipe.
)doc")

        // Control Signals
        .def("start", &RtsiClientInterface::start,
             R"doc(
Send a start signal to the RTSI server.

Returns:
    bool: True if the command was accepted.
)doc")
        .def("pause", &RtsiClientInterface::pause,
             R"doc(
Send a pause signal to the RTSI server.

Returns:
    bool: True if the command was accepted.
)doc")

        // Data Transfer
        .def("send", &RtsiClientInterface::send, py::arg("recipe"),
             R"doc(
Send an RTSI recipe to the controller.

Args:
    recipe (RtsiRecipeSharedPtr): The recipe to send.
)doc")
        .def("receiveData", py::overload_cast<std::vector<RtsiRecipeSharedPtr>&, bool>(&RtsiClientInterface::receiveData),
             py::arg("recipes"), py::arg("read_newest") = false,
             R"doc(
Receive multiple RTSI recipes.

Args:
    recipes (List[RtsiRecipeSharedPtr]): Container to fill with received recipes.
    read_newest (bool, optional): If True, parse only the newest data. Defaults to False.

Returns:
    int: ID of the received recipe, or -1 if none matched.
)doc")
        .def("receiveData", py::overload_cast<RtsiRecipeSharedPtr, bool>(&RtsiClientInterface::receiveData), py::arg("recipe"),
             py::arg("read_newest") = false,
             R"doc(
Receive a single RTSI recipe.

Args:
    recipe (RtsiRecipeSharedPtr): The recipe to populate.
    read_newest (bool, optional): If True, parse only the newest data. Defaults to False.

Returns:
    bool: True if data was received successfully.
)doc")

        // Status Queries
        .def("isConnected", &RtsiClientInterface::isConnected,
             R"doc(
Check whether the client is connected.

Returns:
    bool: True if connected.
)doc")
        .def("isStarted", &RtsiClientInterface::isStarted,
             R"doc(
Check whether data synchronization has started.

Returns:
    bool: True if synchronization is active.
)doc")
        .def("isReadAvailable", &RtsiClientInterface::isReadAvailable,
             R"doc(
Check if data is available to read without blocking.

Returns:
    bool: True if data is available.
)doc");
}
