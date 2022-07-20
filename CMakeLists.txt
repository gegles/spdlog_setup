cmake_minimum_required(VERSION 3.16)

# Conan
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

project(spdlog_setup
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(spdlog REQUIRED CONFIG)
find_package(fmt REQUIRED CONFIG)
find_package(cpptoml REQUIRED CONFIG)

# spdlog_setup
add_library(spdlog_setup INTERFACE)
target_include_directories(spdlog_setup INTERFACE include)
target_link_libraries(spdlog_setup INTERFACE spdlog::spdlog_header_only cpptoml::cpptoml fmt::fmt-header-only)

# spdlog_setup_sources (for IDEs)
if (XCODE OR MSVC)
  add_custom_target(spdlog_setup_sources SOURCES
    include/spdlog_setup/spdlog_setup.hpp
    include/spdlog_setup/details/conf_impl.hpp
    include/spdlog_setup/setup_error.hpp
    include/spdlog_setup/details/template_impl.hpp)
endif ()

# Tests
option(SPDLOG_SETUP_BUILD_TESTS "Build spdlog_setup tests" ON)
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
