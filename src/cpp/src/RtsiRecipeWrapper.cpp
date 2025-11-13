// SPDX-License-Identifier: MIT
// Copyright (c) 2025, Elite Robots.
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <Elite/RtsiRecipe.hpp>

namespace py = pybind11;
using namespace ELITE;

void bindRtsiRecipe(py::module_ &m) {
    py::class_<RtsiRecipe, RtsiRecipeSharedPtr>(m, "RtsiRecipe")
        .def("getRecipe", &RtsiRecipe::getRecipe, "Return the list of variable names.")

        .def("getID", &RtsiRecipe::getID, "Return the recipe ID (1-254).")

        .def(
            "getValue",
            [](RtsiRecipe &r, const std::string &name) {
                // 1) bool
                try {
                    bool v;
                    if (r.getValue<bool>(name, v)) return py::object(py::bool_(v));
                } catch (const std::bad_variant_access &) { /* ignore */
                }

                // 2) int32
                try {
                    int32_t v;
                    if (r.getValue<int32_t>(name, v)) return py::object(py::int_(v));
                } catch (const std::bad_variant_access &) { /* ignore */
                }

                // 3) uint32
                try {
                    uint32_t v;
                    if (r.getValue<uint32_t>(name, v)) return py::object(py::int_(v));
                } catch (const std::bad_variant_access &) { /* ignore */
                }

                // 4) double
                try {
                    double v;
                    if (r.getValue<double>(name, v)) return py::object(py::float_(v));
                } catch (const std::bad_variant_access &) { /* ignore */
                }

                // 5) vector3d_t
                try {
                    vector3d_t v;
                    if (r.getValue<vector3d_t>(name, v)) return py::cast(std::vector<double>{v[0], v[1], v[2]});
                } catch (const std::bad_variant_access &) { /* ignore */
                }

                // 6) vector6d_t
                try {
                    vector6d_t v;
                    if (r.getValue<vector6d_t>(name, v)) return py::cast(std::vector<double>{v[0], v[1], v[2], v[3], v[4], v[5]});
                } catch (const std::bad_variant_access &) { /* ignore */
                }

                throw std::runtime_error("Variable '" + name + "' not found or unsupported type");
            },
            py::arg("name"),
            R"doc(
Retrieve the value of a variable by name.

Args:
    name (str): Variable name.

Returns:
    bool | int | float | List[float]:
        The value converted to a Python type.

Raises:
    RuntimeError: If the variable does not exist or its type is not supported.
)doc")
        // 通用 set: 从 Python object 推断类型，然后调用模板
        .def(
            "setValue",
            [](RtsiRecipe &r, const std::string &name, py::object obj) {
                bool ok = false;
                if (py::isinstance<py::bool_>(obj)) {
                    ok = r.setValue<bool>(name, obj.cast<bool>());
                } else if (py::isinstance<py::int_>(obj)) {
                    ok = r.setValue(name, obj.cast<int64_t>());
                } else if (py::isinstance<py::float_>(obj)) {
                    ok = r.setValue<double>(name, obj.cast<double>());
                } else if (py::isinstance<py::tuple>(obj)) {
                    // Check if it's a vector3d_t or vector6d_t
                    auto tup = obj.cast<std::vector<double>>();
                    if (tup.size() == 3) {
                        vector3d_t v{tup[0], tup[1], tup[2]};
                        ok = r.setValue(name, v);
                    } else if (tup.size() == 6) {
                        vector6d_t v{tup[0], tup[1], tup[2], tup[3], tup[4], tup[5]};
                        ok = r.setValue(name, v);
                    }
                }
                if (!ok) {
                    throw std::runtime_error("Cannot convert Python object to any supported RTSI type");
                }
            },
            py::arg("name"), py::arg("value"),
            R"(
Set the value of a variable by name.

Args:
    name (str): variable name
    value: any of the supported types (bool, int, float, tuple, etc.)
)");
}
