import subprocess

from setuptools import setup

from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [Pybind11Extension("genetic", ["bind/bind.cpp"])]

setup(
    name="genetic",
    ext_modules=ext_modules,
    version="0.0.1",
    cmdclass={"build_ext": build_ext},
)

subprocess.check_call(["stubgen", "-m", "genetic", "-o", "."])
