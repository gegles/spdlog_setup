from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.build import check_min_cppstd
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps
from conan.tools.files import get, copy
from conan.tools.layout import basic_layout
from conan.tools.scm import Version
import os

required_conan_version = ">=1.52.0"


class SpdlogSetupConan(ConanFile):
    name = "spdlog_setup"
    version = "1.2.0"
    description = "Setup spdlog via a TOML config file"
    license = "MIT"
    url = "https://github.com/conan-io/conan-center-index"
    homepage = "https://github.com/gegles/spdlog_setup"
    topics = ('spdlog', 'logging', 'header-only', 'toml', 'cpptoml')
    package_type = "header-library"
    settings = "os", "arch", "compiler", "build_type"
    no_copy_source = True
    exports_sources = "include/*", "LICENSE", "CMakeLists.txt", "test/*"
    options = {
        "use_std_fmt": [True, False],
    }
    default_options = {
        "use_std_fmt": False,
    }

    @property
    def _min_cppstd(self):
        return 20 if self.options.use_std_fmt else 17

    @property
    def _compilers_minimum_version(self):
        if self.options.use_std_fmt:
            return {
                "Visual Studio": "16",
                "msvc": "192",
                "gcc": "13",
                "clang": "14",
                "apple-clang": "15",
            }
        return {
            "Visual Studio": "16",
            "msvc": "192",
            "gcc": "8",
            "clang": "7",
            "apple-clang": "12.0",
        }

    def layout(self):
        # For header-only with exports_sources, no separate src folder needed
        basic_layout(self)

    def requirements(self):
        self.requires("cpptoml/0.1.1")
        self.requires("spdlog/[>=1.15 <2]")
        if not self.options.use_std_fmt:
            self.requires("fmt/[>=10 <=12]")

    def configure(self):
        # Configure spdlog to be header-only to match this library's nature
        self.options["spdlog"].header_only = True
        # Match spdlog's use_std_fmt with our own
        self.options["spdlog"].use_std_fmt = self.options.use_std_fmt

    def build_requirements(self):
        if not self.conf.get("tools.build:skip_test", default=False):
            self.test_requires("catch2/3.11.0")

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
            tc.variables["SPDLOG_SETUP_USE_STD_FORMAT"] = self.options.use_std_fmt
            tc.generate()
            deps = CMakeDeps(self)
            deps.generate()

    def build(self):
        if not self.conf.get("tools.build:skip_test", default=False):
            cmake = CMake(self)
            cmake.configure()
            cmake.build()
            cmake.test()

    def source(self):
        # Only download sources if conan_data exists (e.g., when building from conan-center)
        # For local development, sources are exported via exports_sources
        if self.conan_data:
            get(self, **self.conan_data["sources"][self.version], strip_root=True)

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

        if self.options.use_std_fmt:
            self.cpp_info.defines.append("SPDLOG_SETUP_USE_STD_FORMAT")
