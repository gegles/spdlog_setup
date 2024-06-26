from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.build import check_min_cppstd
from conan.tools.files import copy
from conan.tools.scm import Version
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps, cmake_layout

import os

required_conan_version = ">=1.52.0"


class SpdlogSetupConan(ConanFile):
    name = "spdlog_setup"
    version = "1.1.1"
    description = "Setup spdlog via a TOML config file"
    license = "MIT"
    url = "https://github.com/conan-io/conan-center-index"
    homepage = "https://github.com/gegles/spdlog_setup"
    topics = ('spdlog', 'logging', 'header-only', 'TOML', 'cpptoml')
    package_type = "header-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "include/*", "test/*", "CMakeLists.txt", "cmake/*", "LICENSE"
    no_copy_source = True
    default_options = {"fmt/*:header_only": True,
                       "spdlog/*:header_only": True}

    @property
    def _min_cppstd(self):
        return 14

    @property
    def _compilers_minimum_version(self):
        return {
            "Visual Studio": "16",
            "msvc": "192",
            "gcc": "8",
            "clang": "7",
            "apple-clang": "12.0",
        }

    def layout(self):
        cmake_layout(self)

    def build_requirements(self):
        self.test_requires("catch2/3.6.0")

    def requirements(self):
        self.requires("cpptoml/0.1.1")
        self.requires("spdlog/1.14.1")
        self.requires("fmt/10.2.1")

    def package_id(self):
        self.info.clear()

    def validate(self):
        if self.settings.compiler.get_safe("cppstd"):
            check_min_cppstd(self, self._min_cppstd)
        minimum_version = self._compilers_minimum_version.get(str(self.settings.compiler), False)
        if minimum_version and Version(self.settings.compiler.version) < minimum_version:
            raise ConanInvalidConfiguration(
                f"{self.ref} requires C++{self._min_cppstd}, which your compiler does not support."
            )

    def generate(self):
        if not self.conf.get("tools.build:skip_test", default=False):
            tc = CMakeToolchain(self)
            tc.generate()
            deps = CMakeDeps(self)
            deps.generate()

    def build(self):
        if not self.conf.get("tools.build:skip_test", default=False):
            cmake = CMake(self)
            cmake.configure()
            cmake.build()
            cmake.test()

    def package(self):
        copy(self, pattern="LICENSE", dst=os.path.join(self.package_folder, "licenses"), src=self.source_folder)
        copy(
            self,
            pattern="*.hpp",
            dst=os.path.join(self.package_folder, "include"),
            src=os.path.join(self.source_folder, "include"),
        )

    def package_info(self):
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
        self.cpp_info.set_property("cmake_file_name", "spdlog_setup")
        self.cpp_info.set_property("cmake_target_name", "spdlog_setup::spdlog_setup")

        # TODO: to remove in conan v2 once cmake_find_package_* generators removed
        self.cpp_info.filenames["cmake_find_package"] = "SPDLOG_SETUP"
        self.cpp_info.filenames["cmake_find_package_multi"] = "spdlog_setup"
        self.cpp_info.names["cmake_find_package"] = "SPDLOG_SETUP"
        self.cpp_info.names["cmake_find_package_multi"] = "spdlog_setup"
