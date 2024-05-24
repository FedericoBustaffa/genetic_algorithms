import subprocess

from setuptools import setup

from pybind11.setup_helpers import Pybind11Extension, build_ext

# generate file for intellisense
subprocess.check_call(["stubgen", "-m", "genetic", "-o", "."])

ext_modules = [Pybind11Extension("genetic", ["src/bind.cpp"])]

setup(
    name="genetic",
    ext_modules=ext_modules,
    version="0.0.1",
    cmdclass={"build_ext": build_ext},
)
