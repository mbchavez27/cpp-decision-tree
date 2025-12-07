#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "./utils/decision_tree.hpp"

namespace py = pybind11;

PYBIND11_MODULE(cpp_mac_learn, m)
{
     py::class_<DecisionTree>(m, "DecisionTree")
         .def(py::init<int>(), py::arg("max_depth") = 5)
         .def("fit", [](DecisionTree &self,
                        const std::vector<std::vector<double>> &X,
                        const std::vector<double> &y)
              { self.fit(X, y); })
         .def("predict_one", [](DecisionTree &self, const std::vector<double> &x)
              { return self.predict(x); })
         .def("predict", [](DecisionTree &self,
                            const std::vector<std::vector<double>> &X)
              { return self.predict(X); });
}
