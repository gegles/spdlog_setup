#!/usr/bin/env python
# -*- coding: utf-8 -*-
from conans import CMake
from conan import ConanFile

class SpdlogSetupConan(ConanFile):
    name = "spdlog_setup"
    version = "1.1.0"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "include/*", "test/*", "CMakeLists.txt"
    no_copy_source = True
    generators = "CMakeToolchain", "CMakeDeps"

    def config_options(self):
        self.options['fmt'].header_only = True
        self.options['spdlog'].header_only = True

    def requirements(self):
        self.requires("catch2/3.0.1")
        self.requires("cpptoml/0.1.1")
        self.requires("spdlog/1.10.0")
        self.requires("fmt/8.1.1")

    def build(self): # this is not building a library, just tests
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.test()

    def package(self):
        self.copy("*.hpp")

    def package_id(self):
        self.info.header_only()
