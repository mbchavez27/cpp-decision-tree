from setuptools import setup, Extension
import pybind11

ext_modules = [
    Extension(
        "cpp_mac_learn",
        [
            "bindings.cpp",                    # Python bindings
            "decision_tree/decision_tree.cpp", # C++ code
            "decision_tree/gini.cpp",          # C++ code
        ],
        include_dirs=[
            pybind11.get_include(),
            "utils",   # headers: decision_tree.hpp, gini.hpp, node.hpp
        ],
        language="c++",
        extra_compile_args=["-std=c++17"],
    )
]

setup(
    name="cpp_mac_learn",
    version="0.1.0",
    ext_modules=ext_modules,
)
