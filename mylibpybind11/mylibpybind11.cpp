#include <pybind11/pybind11.h>

uint64_t count_byte_doubles(char * str) {
  uint64_t count = 0;
  while (str[0] && str[1]) {
    if (str[0] == str[1]) count++;
    str++;
  }
  return count;
}

namespace py = pybind11;

PYBIND11_MODULE(mylibpybind11, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------
        .. currentmodule:: mylibpybind11
        .. autosummary::
           :toctree: _generate
           add
           subtract
    )pbdoc";

    m.def("count_byte_doubles", &count_byte_doubles, R"pbdoc(
        Count byte doubles
    )pbdoc");

    m.attr("__version__") = "dev";

}