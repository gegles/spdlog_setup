# `spdlog_setup` (spdlog setup)

## Overview

Header-only [`spdlog`](https://github.com/gabime/spdlog) file-based setup
library for convenience in initializing spdlog. It is using
[`TOML`](https://github.com/toml-lang/toml) configuration, a format that is
simple and easy-to-read.

## Requirements

Requires at least `Conan v1.59` or `Conan v2.x`

## Features

- Header-only
- Initialization of `spdlog` sinks, patterns and loggers based on `TOML`
  configuration file.
- Tag replacement (e.g. "{tagname}-log.txt") within the `TOML` configuration
  file.
- Throw exception describing the error during the parsing of the config file.

## Changelog

See [CHANGELOG.md](./CHANGELOG.md) for more details.

## Dependencies

This repository uses the following external dependencies directly:

- [`Catch`](https://github.com/philsquared/Catch) (only for unit-tests, not
  included in installation)
- [`spdlog`](https://github.com/gabime/spdlog)
- [`cpptoml`](https://github.com/skystrife/cpptoml)
- [`fmt`](https://github.com/fmtlib/fmt.git)

## How to Build

- `conan build -b mising .`

## Supported Sinks

- `stdout_sink_st`
- `stdout_sink_mt`
- `stderr_sink_st`
- `stderr_sink_mt`
- `color_stdout_sink_st`
- `color_stdout_sink_mt`
- `color_stderr_sink_st`
- `color_stderr_sink_mt`
- `basic_file_sink_st`
- `basic_file_sink_mt`
- `rotating_file_sink_st`
- `rotating_file_sink_mt`
- `daily_file_sink_st`
- `daily_file_sink_mt`
- `null_sink_st`
- `null_sink_mt`
- `syslog_sink` (only for Linux, `SPDLOG_ENABLE_SYSLOG` preprocessor definition
  must be defined before any `spdlog`/`spdlog_setup` header is included)

Currently `ostream_sink` and `dist_sink` do not fit into the use case and are
not supported.

For more information about how the above sinks work in `spdlog`, please refer to
the original `spdlog` sinks wiki page at:
<https://github.com/gabime/spdlog/wiki/4.-Sinks>.

## TOML Configuration Example

### Static File Configuration

```toml
# level is optional for both sinks and loggers
# level for error logging is 'err', not 'error'
# _st => single threaded, _mt => multi threaded
# syslog_sink is automatically thread-safe by default, no need for _mt suffix

# max_size supports suffix
# - T (terabyte)
# - G (gigabyte)
# - M (megabyte)
# - K (kilobyte)
# - or simply no suffix (byte)

# check out https: // github.com/gabime/spdlog/wiki/3.-Custom-formatting
global_pattern = "[%Y-%m-%dT%T%z] [%L] <%n>: %v"

[[sink]]
name = "console_st"
type = "stdout_sink_st"

[[sink]]
name = "console_mt"
type = "stdout_sink_mt"

[[sink]]
name = "color_console_st"
type = "color_stdout_sink_st"

[[sink]]
name = "color_console_mt"
type = "color_stdout_sink_mt"

[[sink]]
name = "file_out"
type = "basic_file_sink_st"
filename = "log/spdlog_setup.log"
# truncate field is optional
# truncate = false (default)
level = "info"
# optional flag to indicate the set - up to create the log dir first
create_parent_dir = true

[[sink]]
name = "file_err"
type = "basic_file_sink_mt"
filename = "log/spdlog_setup_err.log"
truncate = true
level = "err"
# to show that create_parent_dir is indeed optional(defaults to false)

[[sink]]
name = "rotate_out"
type = "rotating_file_sink_st"
base_filename = "log/rotate_spdlog_setup.log"
max_size = "1M"
max_files = 10
level = "info"

[[sink]]
name = "rotate_err"
type = "rotating_file_sink_mt"
base_filename = "log/rotate_spdlog_setup_err.log"
max_size = "1M"
max_files = 10
level = "err"

[[sink]]
name = "daily_out"
type = "daily_file_sink_st"
base_filename = "log/daily_spdlog_setup.log"
rotation_hour = 17
rotation_minute = 30
level = "info"

[[sink]]
name = "daily_err"
type = "daily_file_sink_mt"
base_filename = "log/daily_spdlog_setup_err.log"
rotation_hour = 17
rotation_minute = 30
level = "err"

[[sink]]
name = "null_sink_st"
type = "null_sink_st"

[[sink]]
name = "null_sink_mt"
type = "null_sink_mt"

# only works for Linux
[[sink]]
name = "syslog_st"
type = "syslog_sink_st"
# generally no need to fill up the optional fields below
# ident = "" (default)
# syslog_option = 0 (default)
# syslog_facility = LOG_USER (default macro value)

# only works for Linux
[[sink]]
name = "syslog_mt"
type = "syslog_sink_mt"
# generally no need to fill up the optional fields below
# ident = "" (default)
# syslog_option = 0 (default)
# syslog_facility = LOG_USER (default macro value)

# only works for Windows
[[sink]]
name = "msvc_st"
type = "msvc_sink_st"

# only works for Windows
[[sink]]
name = "msvc_mt"
type = "msvc_sink_mt"

[[pattern]]
name = "succient"
value = "%c-%L: %v"

[[logger]]
name = "root"
sinks = [
    "console_st", "console_mt",
    "color_console_st", "color_console_mt",
    "daily_out", "daily_err",
    "file_out", "file_err",
    "rotate_out", "rotate_err",
    "null_sink_st", "null_sink_mt",
    "syslog_st", "syslog_mt"]
level = "trace"

[[logger]]
name = "windows_only"
sinks = ["msvc_st", "msvc_mt"]

[[logger]]
name = "console"
sinks = ["console_st", "console_mt"]
pattern = "succient"

# Async

[global_thread_pool]
queue_size = 8192
num_threads = 1

[[thread_pool]]
name = "tp"
queue_size = 4096
num_threads = 2

[[logger]]
type = "async"
name = "global_async"
sinks = ["console_mt"]
pattern = "succient"

[[logger]]
type = "async"
name = "local_async"
sinks = ["console_mt"]
pattern = "succient"
thread_pool = "tp"
overflow_policy = "overrun_oldest"  # block (default) | overrun_oldest
```

### Tagged-Base Pre-TOML File Configuration

```toml
# level is optional for both sinks and loggers
# level for error logging is 'err', not 'error'

# max_size supports suffix
# - T (terabyte)
# - G (gigabyte)
# - M (megabyte)
# - K (kilobyte)
# - or simply no suffix (byte)

[[sink]]
name = "console"
type = "stdout_sink_mt"

[[sink]]
name = "rotate_out"
type = "rotating_file_sink_mt"
base_filename = "log/{index}-info/simple-{path}.log"
max_size = "1M"
max_files = 10
level = "info"
# optional flag to indicate the set - up to create the log dir first
create_parent_dir = true

[[sink]]
name = "simple_err"
type = "basic_file_sink_mt"
filename = "log/{index}-err/simple-{path}.log"
truncate = false
level = "err"
# optional flag to indicate the set - up to create the log dir first
create_parent_dir = true

[[logger]]
name = "root"
sinks = ["console", "rotate_out", "simple_err"]
level = "trace"
```

## Use Examples

### Static Configuration File

```c++
#include <spdlog_setup/spdlog_setup.hpp>
#include <iostream>
#include <string>

int main() {
    try {
        // spdlog_setup::setup_error thrown if file not found
        spdlog_setup::from_file("log_conf.toml");

        // assumes that root logger has been initialized
        auto logger = spdlog::get("root");
        logger->trace("trace message");
        logger->debug("debug message");
        logger->info("info message");
        logger->warn("warn message");
        logger->error("error message");
        logger->critical("critical message");

        // ...
    } catch (const spdlog_setup::setup_error &) {
        // ...
    } catch (const std::exception &) {
        // ...
    }
}
```

### Tagged Based Configuration File

```c++
#include <spdlog_setup/spdlog_setup.hpp>
#include <string>

int main(const int argc, const char * argv[]) {
    // assumes both index and path are given by command line arguments

    try {
        // gets index integer, e.g. 123
        const auto index = std::stoi(argv[1]);

        // gets path string, e.g. a/b/c
        const auto path = std::string(argv[2]);

        // performs parsing with dynamic tag value replacements
        // tags are anything content that contains {xxx}, where xxx is the name
        // of the tag to be replaced
        spdlog_setup::from_file_with_tag_replacement(
            "log_conf.pre.toml",
            // replaces {index} with actual value in current variable index via
            // fmt mechanism
            fmt::arg("index", index),
            // replaces {path} with actual value in current variable path
            fmt::arg("path", path));

        auto logger = spdlog::get("root");
        // ...
    } catch (const spdlog_setup::setup_error &) {
        // ...
    } catch (const std::exception &) {
        // ...
    }
}
```

## Notes

- Make sure that the directory for the log files to reside in exists before
  using `spdlog`, unless the `create_parent_dir` flag is set to true for the
  sink.
- For the current set of unit tests, the working directory must be at the git
  root directory or in `build` directory so that the TOML configuration files in
  `config` directory can be found.

## Contributions

Pull requests are welcome!

To make the code formatting more objective, `clang-format` is used to format
all the source code files.

Please try to run

```bash
./reformat.sh
```

which will pull the appropriate Docker image to run the formatting command over
the entire repository directory.
