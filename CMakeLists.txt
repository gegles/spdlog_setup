cmake_minimum_required(VERSION 3.16)
project(spdlog_setup VERSION 1.1.1 LANGUAGES CXX)

find_package(spdlog REQUIRED CONFIG)
find_package(fmt REQUIRED CONFIG)
find_package(cpptoml REQUIRED CONFIG)

option(SPDLOG_SETUP_SPDLOG_HEADER_ONLY "Use header-only version of spdlog" ON)
option(SPDLOG_SETUP_FMT_HEADER_ONLY "Use header-only version of fmt" ON)
option(SPDLOG_SETUP_BUILD_TESTS "Build spdlog_setup tests" ON)

# spdlog_setup
add_library(spdlog_setup INTERFACE)
target_include_directories(spdlog_setup INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(spdlog_setup INTERFACE cxx_std_14)

target_link_libraries(spdlog_setup INTERFACE cpptoml)
if (SPDLOG_SETUP_SPDLOG_HEADER_ONLY)
    target_link_libraries(spdlog_setup INTERFACE spdlog::spdlog_header_only)
else ()
    target_link_libraries(spdlog_setup INTERFACE spdlog::spdlog)
endif ()
if (SPDLOG_SETUP_FMT_HEADER_ONLY)
    target_link_libraries(spdlog_setup INTERFACE fmt::fmt-header-only)
else ()
    target_link_libraries(spdlog_setup INTERFACE fmt::fmt)
endif ()

# spdlog_setup_sources (for IDEs)
if (XCODE OR MSVC)
  add_custom_target(spdlog_setup_sources SOURCES
    include/spdlog_setup/spdlog_setup.hpp
    include/spdlog_setup/details/conf_impl.hpp
    include/spdlog_setup/setup_error.hpp
    include/spdlog_setup/details/template_impl.hpp)
endif ()

# Tests
if (SPDLOG_SETUP_BUILD_TESTS)
  set(THREADS_PREFER_PTHREAD_FLAG ON)
  find_package(Threads REQUIRED)
  find_package(Catch2 3 REQUIRED)
  enable_testing()

  add_executable(spdlog_setup_tests)

  target_sources(spdlog_setup_tests PRIVATE
      test/loggers.test.cpp
      test/others.test.cpp
      test/sinks.test.cpp
      test/thread_pool.test.cpp)

  if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(spdlog_setup_tests PRIVATE -Wno-potentially-evaluated-expression -Wno-deprecated-declarations)
  endif ()
  target_link_libraries(spdlog_setup_tests PRIVATE Catch2::Catch2WithMain spdlog_setup Threads::Threads)
  include(Catch)
  catch_discover_tests(spdlog_setup_tests)
endif ()


# Installation
install(DIRECTORY include/spdlog_setup DESTINATION include)

install(TARGETS spdlog_setup EXPORT spdlog_setup_targets)
install(EXPORT spdlog_setup_targets
    FILE spdlog_setup-targets.cmake
    NAMESPACE spdlog_setup::
    DESTINATION lib/cmake/spdlog_setup
)

include(CMakePackageConfigHelpers)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/spdlog_setup-config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/spdlog_setup-config.cmake"
    INSTALL_DESTINATION lib/cmake/spdlog_setup
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
write_basic_package_version_file(
    "spdlog_setup-config-version.cmake"
    VERSION ${spdlog_setup_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/spdlog_setup-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/spdlog_setup-config-version.cmake"
    DESTINATION lib/cmake/spdlog_setup
)
