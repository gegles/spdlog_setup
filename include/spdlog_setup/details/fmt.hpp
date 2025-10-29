/**
 * Conditional format library inclusion for spdlog_setup.
 * Allows using either std::format (C++20) or fmt::format (external library).
 * @author Chen Weiguang
 * @version 0.3.3-pre
 */

#pragma once

// Use std::format if SPDLOG_SETUP_USE_STD_FORMAT is defined
#ifdef SPDLOG_SETUP_USE_STD_FORMAT
    #include <format>
    namespace spdlog_setup {
        namespace fmt {
            using std::format;
        }
    }
#else
    // Use external fmt library
    #include <fmt/format.h>
    namespace spdlog_setup {
        namespace fmt {
            using ::fmt::format;
        }
    }
#endif
