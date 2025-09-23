#include "PrimaryPackageWrapper.hpp"
#include "Elite/PrimaryPackage.hpp"

#include <pybind11/pytypes.h>

namespace py = pybind11;
using namespace ELITE;

class PyPrimaryPackage : public PrimaryPackage {
    using PrimaryPackage::PrimaryPackage;

    void parser(int len, const std::vector<uint8_t>::const_iterator& iter) override {
        py::gil_scoped_acquire gil;
        py::bytes data(reinterpret_cast<const char*>(&*iter), len);
        PYBIND11_OVERRIDE_PURE(void, PrimaryPackage, parser, data);
    }
};

void bindPrimaryPackage(py::module_& m) {
    py::class_<PrimaryPackage, PyPrimaryPackage, std::shared_ptr<PrimaryPackage>>(m, "PrimaryPackage",
                                                                                  R"doc(
            Inherit this class to obtain the data of the primary port.
         )doc")
        .def(py::init<int>())
        .def("getType", &PrimaryPackage::getType,
             R"doc(
            Get the sub-package type.

            Returns:
                int: Sub-package type
         )doc");
}
