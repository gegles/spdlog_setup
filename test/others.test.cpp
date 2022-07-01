/**
 * Unit tests implementation.
 * @author Chen Weiguang
 * @version 0.3.3-pre
 */

#include <spdlog_setup/spdlog_setup.hpp>
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>

namespace examples {
#ifdef _WIN32
static constexpr auto FULL_CONF = R"x(
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
    level = "info"
    create_parent_dir = true

    [[sink]]
    name = "file_err"
    type = "basic_file_sink_mt"
    filename = "log/spdlog_setup_err.log"
    truncate = true
    level = "err"

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

    [[sink]]
    name = "msvc_sink_st"
    type = "msvc_sink_st"

    [[sink]]
    name = "msvc_sink_mt"
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
        "msvc_sink_st", "msvc_sink_mt"]
    level = "trace"

    [[logger]]
    name = "console"
    sinks = ["console_st", "console_mt"]
    pattern = "succient"

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
)x";
#else
static constexpr auto FULL_CONF = R"x(
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
    level = "info"
    create_parent_dir = true

    [[sink]]
    name = "file_err"
    type = "basic_file_sink_mt"
    filename = "log/spdlog_setup_err.log"
    truncate = true
    level = "err"

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

    [[sink]]
    name = "syslog_st"
    type = "syslog_sink_st"

    [[sink]]
    name = "syslog_mt"
    type = "syslog_sink_mt"

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
    name = "console"
    sinks = ["console_st", "console_mt"]
    pattern = "succient"

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
)x";
#endif

static constexpr auto PRE_CONF = R"x(
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
    create_parent_dir = true

    [[sink]]
    name = "simple_err"
    type = "basic_file_sink_mt"
    filename = "log/{index}-err/simple-{path}.log"
    truncate = false
    level = "err"
    create_parent_dir = true

    [[logger]]
    name = "root"
    sinks = ["console", "rotate_out", "simple_err"]
    level = "trace"
)x";

static constexpr auto OVERRIDE_CONF = R"x(
    [[sink]]
    name = "console_st"
    level = "err"

    [[sink]]
    name = "console_mt"
    level = "critical"

    [[sink]]
    name = "console_another"
    type = "stdout_sink_st"
    level = "trace"

    [[pattern]]
    name = "super-succient"
    value = "%L: %v"

    [[logger]]
    name = "console"
    sinks = ["console_st", "console_mt", "console_another"]
    pattern = "super-succient"
    level = "trace"
)x";

static constexpr auto OVERRIDE_PRE_CONF = R"x(
    [[sink]]
    name = "rotate_out"
    base_filename = "log/{index}-info/simple-{path}-{hash}.log"
    max_size = "1K"
    max_files = 3
    level = "trace"
    create_parent_dir = true

    [[sink]]
    name = "simple_err"
    filename = "log/{index}-err/simple-{path}-{hash}.log"
    level = "warn"
    create_parent_dir = true
)x";

static constexpr auto SIMPLE_CONSOLE_LOGGER_CONF = R"x(
    [[pattern]]
    name = "easy"
    value = "%L: %v"

    [[logger]]
    name = "not-console"
    pattern = "easy"
    level = "info"

    [[logger]]
    name = "console"
    pattern = "easy"
    level = "trace"
)x";

class tmp_file {
public:
  tmp_file(const std::string& content) : file_path(std::tmpnam(nullptr))
  {
    std::ofstream ostr(file_path);
    ostr << content;
  }

  tmp_file() : tmp_file("") {}

  ~tmp_file() { std::remove(file_path.c_str()); }

  auto get_file_path() const -> const std::string& { return file_path; }

private:
  std::string file_path;
};

inline auto
get_full_conf_tmp_file() -> tmp_file
{
  return tmp_file(FULL_CONF);
}

inline auto
get_pre_conf_tmp_file() -> tmp_file
{
  return tmp_file(PRE_CONF);
}

inline auto
get_override_conf_tmp_file() -> tmp_file
{
  return tmp_file(OVERRIDE_CONF);
}

inline auto
get_override_pre_conf_tmp_file() -> tmp_file
{
  return tmp_file(OVERRIDE_PRE_CONF);
}

inline auto
get_simple_console_logger_conf_tmp_file() -> tmp_file
{
  return tmp_file(SIMPLE_CONSOLE_LOGGER_CONF);
}

template <class Iterable>
auto
dist(const Iterable& iterable) -> ptrdiff_t
{
  return std::distance(std::begin(iterable), std::end(iterable));
}

template <class Iterable>
auto
get_index(const Iterable& iterable, const size_t index) -> typename Iterable::const_iterator::reference
{

  return *std::next(std::begin(iterable), index);
}
} // namespace examples

// spdlog_setup
using fmt::arg;
using spdlog::level::level_enum;
using spdlog_setup::setup_error;
using spdlog_setup::details::render;

namespace names = spdlog_setup::details::names;
using names::LEVEL;
using names::LOGGER_TABLE;
using names::NAME;
using names::PATTERN_TABLE;
using names::VALUE;

// std
using std::cerr;
using std::distance;
using std::getline;
using std::ifstream;
using std::string;
using std::unordered_map;

TEST_CASE("Parse max size no suffix", "[parse_max_size_no_suffix]")
{
  REQUIRE(123 == spdlog_setup::details::parse_max_size("123"));
}

TEST_CASE("Parse max size byte", "[parse_max_size_byte]")
{
  REQUIRE(123 == spdlog_setup::details::parse_max_size("123B"));
}

TEST_CASE("Parse max size kilo", "[parse_max_size_kilo]")
{
  REQUIRE(123 * 1024 == spdlog_setup::details::parse_max_size("123K"));
}

TEST_CASE("Parse max size kilobyte", "[parse_max_size_kilobyte]")
{
  REQUIRE(123 * 1024 == spdlog_setup::details::parse_max_size("123KB"));
}

TEST_CASE("Parse max size mega", "[parse_max_size_mega]")
{
  REQUIRE(123 * 1024 * 1024 == spdlog_setup::details::parse_max_size("123M"));
}

TEST_CASE("Parse max size megabyte", "[parse_max_size_megabyte]")
{
  REQUIRE(123 * 1024 * 1024 == spdlog_setup::details::parse_max_size("123MB"));
}

TEST_CASE("Parse max size giga", "[parse_max_size_giga]")
{
  REQUIRE(123ull * 1024 * 1024 * 1024 == spdlog_setup::details::parse_max_size("123G"));
}

TEST_CASE("Parse max size gigabyte", "[parse_max_size_gigabyte]")
{
  REQUIRE(123ull * 1024 * 1024 * 1024 == spdlog_setup::details::parse_max_size("123GB"));
}

TEST_CASE("Parse max size tera", "[parse_max_size_tera]")
{
  REQUIRE(123ull * 1024 * 1024 * 1024 * 1024 == spdlog_setup::details::parse_max_size("123T"));
}

TEST_CASE("Parse max size terabyte", "[parse_max_size_terabyte]")
{
  REQUIRE(123ull * 1024 * 1024 * 1024 * 1024 == spdlog_setup::details::parse_max_size("123TB"));
}

TEST_CASE("Parse max size weird", "[parse_max_size_weird]")
{
  REQUIRE(45672ull * 1024 * 1024 == spdlog_setup::details::parse_max_size("\n  45672  MB\t"));
}

TEST_CASE("Parse max size error", "[parse_max_size_error]")
{
  REQUIRE_THROWS_AS(spdlog_setup::details::parse_max_size(" 1x2x3K"), setup_error);
}

TEST_CASE("Parse TOML file for set-up", "[from_file]")
{
  spdlog::drop_all();

  const auto tmp_file = examples::get_full_conf_tmp_file();
  spdlog_setup::from_file(tmp_file.get_file_path());

  const auto root_logger = spdlog::get("root");
  REQUIRE(root_logger != nullptr);

  root_logger->trace("Test Message - Trace!");
  root_logger->debug("Test Message - Debug!");
  root_logger->info("Test Message - Info!");
  root_logger->warn("Test Message - Warn!");
  root_logger->error("Test Message - Error!");
  root_logger->critical("Test Message - Critical!");

  const auto console_logger = spdlog::get("console");
  REQUIRE(console_logger != nullptr);

  console_logger->info("Console Message - Info!");
  console_logger->error("Console Message - Error!");
}

//TEST_CASE("Parse pre-TOML file for set-up", "[from_file_with_tag_replacement]")
//{
//  spdlog::drop_all();
//
//  const auto tmp_file = examples::get_pre_conf_tmp_file();
//
//  spdlog_setup::from_file_with_tag_replacement(tmp_file.get_file_path(), arg("index", 123),
//                                               arg("path", "spdlog_setup"));
//
//  const auto root_logger = spdlog::get("root");
//  REQUIRE(root_logger != nullptr);
//
//  root_logger->trace("Test Message - Trace!");
//  root_logger->debug("Test Message - Debug!");
//  root_logger->info("Test Message - Info!");
//  root_logger->warn("Test Message - Warn!");
//  root_logger->error("Test Message - Error!");
//  root_logger->critical("Test Message - Critical!");
//}

TEST_CASE("Parse TOML file with override for set-up", "[from_file_with_override]")
{
  spdlog::drop_all();

  const auto full_conf_tmp_file     = examples::get_full_conf_tmp_file();
  const auto override_conf_tmp_file = examples::get_override_conf_tmp_file();

  const auto use_override =
      spdlog_setup::from_file_and_override(full_conf_tmp_file.get_file_path(), override_conf_tmp_file.get_file_path());

  REQUIRE(use_override);

  const auto console_logger = spdlog::get("console");
  REQUIRE(console_logger != nullptr);

  console_logger->trace("Console Message - Trace!");
  console_logger->debug("Console Message - Debug!");
  console_logger->info("Console Message - Info!");
  console_logger->warn("Console Message - Warn!");
  console_logger->error("Console Message - Error!");
  console_logger->critical("Console Message - Critical!");
}

TEST_CASE("Parse TOML file with empty override for set-up", "[from_file_with_override_empty]")
{

  spdlog::drop_all();

  const auto full_conf_tmp_file = examples::get_full_conf_tmp_file();

  const auto use_override = spdlog_setup::from_file_and_override(full_conf_tmp_file.get_file_path(), "no_such_file");

  REQUIRE(!use_override);

  const auto console_logger = spdlog::get("console");
  REQUIRE(console_logger != nullptr);

  console_logger->trace("Console Message - Trace!");
  console_logger->debug("Console Message - Debug!");
  console_logger->info("Console Message - Info!");
  console_logger->warn("Console Message - Warn!");
  console_logger->error("Console Message - Error!");
  console_logger->critical("Console Message - Critical!");
}

// TEST_CASE(
//    "Parse pre-TOML file with override for set-up",
//    "[from_file_with_override_with_tag_replacement]") {
//    spdlog::drop_all();
//
//    const auto pre_conf_tmp_file = get_pre_conf_tmp_file().get_file_path();
//    const auto override_pre_conf_tmp_file =
//    get_override_pre_conf_tmp_file().get_file_path();
//
//    const auto use_override =
//        spdlog_setup::from_file_and_override_with_tag_replacement(
//            pre_conf_tmp_file,
//            override_pre_conf_tmp_file,
//            arg("index", 123),
//            arg("path", "spdlog_setup"),
//            arg("hash", "qwerty"));
//
//    REQUIRE(use_override);
//
//    const auto root_logger = spdlog::get("root");
//    REQUIRE(root_logger != nullptr);
//
//    root_logger->trace("Test Message - Trace!");
//    root_logger->debug("Test Message - Debug!");
//    root_logger->info("Test Message - Info!");
//    root_logger->warn("Test Message - Warn!");
//    root_logger->error("Test Message - Error!");
//    root_logger->critical("Test Message - Critical!");
//}

// TEST_CASE(
//    "Parse pre-TOML file with missing override for set-up",
//    "[from_file_with_missing_override_with_tag_replacement]") {
//    spdlog::drop_all();
//
//    const auto index_arg = arg("index", 123);
//    const auto path_arg = arg("path", "spdlog_setup");
//
//    const auto pre_conf_tmp_file = get_pre_conf_tmp_file();
//
//    const auto use_override =
//        spdlog_setup::from_file_and_override_with_tag_replacement(
//            pre_conf_tmp_file.get_file_path(),
//            "no_such_file",
//            index_arg,
//            path_arg);
//
//    REQUIRE(!use_override);
//
//    const auto root_logger = spdlog::get("root");
//    REQUIRE(root_logger != nullptr);
//
//    root_logger->trace("Test Message - Trace!");
//    root_logger->debug("Test Message - Debug!");
//    root_logger->info("Test Message - Info!");
//    root_logger->warn("Test Message - Warn!");
//    root_logger->error("Test Message - Error!");
//    root_logger->critical("Test Message - Critical!");
//}

TEST_CASE("Parse TOML file that does not exist", "[from_file_no_such_file]")
{
  spdlog::drop_all();

  REQUIRE_THROWS_AS(spdlog_setup::from_file("config/no_such_file"), setup_error);
}

//TEST_CASE("Parse pre-TOML file that does not exist", "[from_file_with_tag_replacement_no_such_file]")
//{
//
//  spdlog::drop_all();
//
//  REQUIRE_THROWS_AS(spdlog_setup::from_file_with_tag_replacement("config/no_such_file"), setup_error);
//}

TEST_CASE("Save logger to new file", "[save_logger_to_file_new]")
{
  spdlog::drop_all();
  const auto logger = spdlog::stdout_logger_mt("console");
  logger->set_level(level_enum::warn);

  const auto  tmp_file      = examples::tmp_file();
  const auto& tmp_file_path = tmp_file.get_file_path();

  spdlog_setup::save_logger_to_file(logger, tmp_file_path);

  const auto config = cpptoml::parse_file(tmp_file_path);
  REQUIRE(config != nullptr);

  const auto loggers = config->get_table_array(LOGGER_TABLE);
  REQUIRE(loggers != nullptr);

  const auto& loggers_ref = *loggers;
  REQUIRE(examples::dist(loggers_ref) == 1);

  const auto& console = examples::get_index(loggers_ref, 0);
  REQUIRE(console != nullptr);

  const auto& console_ref = *console;
  REQUIRE(examples::dist(console_ref) == 2);

  const auto name = console_ref.get_as<string>(NAME);
  REQUIRE(static_cast<bool>(name));
  REQUIRE(*name == "console");

  const auto level = console_ref.get_as<string>(LEVEL);
  REQUIRE(static_cast<bool>(level));
  REQUIRE(*level == "warn");
}

TEST_CASE("Save logger to file with existing logger", "[save_logger_to_file_no_overwrite]")
{

  spdlog::drop_all();
  const auto logger = spdlog::stdout_logger_mt("console");
  logger->set_level(level_enum::critical);

  const auto  tmp_file      = examples::get_simple_console_logger_conf_tmp_file();
  const auto& tmp_file_path = tmp_file.get_file_path();

  spdlog_setup::save_logger_to_file(logger, tmp_file_path);

  const auto config = cpptoml::parse_file(tmp_file_path);
  REQUIRE(config != nullptr);

  // patterns

  const auto patterns = config->get_table_array(PATTERN_TABLE);
  REQUIRE(patterns != nullptr);

  const auto& patterns_ref = *patterns;
  REQUIRE(examples::dist(patterns_ref) == 1);

  const auto& pattern = examples::get_index(patterns_ref, 0);
  REQUIRE(pattern != nullptr);

  const auto& pattern_ref = *pattern;

  {
    const auto name = pattern_ref.get_as<string>(NAME);
    REQUIRE(static_cast<bool>(name));
    REQUIRE(*name == "easy");

    const auto value = pattern_ref.get_as<string>(VALUE);
    REQUIRE(static_cast<bool>(value));
    REQUIRE(*value == "%L: %v");
  }

  // loggers

  const auto loggers = config->get_table_array(LOGGER_TABLE);
  REQUIRE(loggers != nullptr);

  const auto& loggers_ref = *loggers;
  REQUIRE(examples::dist(loggers_ref) == 2);

  const auto& not_console = examples::get_index(loggers_ref, 0);
  REQUIRE(not_console != nullptr);

  const auto& not_console_ref = *not_console;
  REQUIRE(examples::dist(not_console_ref) == 3);

  {
    const auto name = not_console_ref.get_as<string>(NAME);
    REQUIRE(static_cast<bool>(name));
    REQUIRE(*name == "not-console");

    const auto pattern = not_console_ref.get_as<string>(names::PATTERN);
    REQUIRE(static_cast<bool>(pattern));
    REQUIRE(*pattern == "easy");

    const auto level = not_console_ref.get_as<string>(LEVEL);
    REQUIRE(static_cast<bool>(level));
    REQUIRE(*level == "info");
  }

  const auto& console = examples::get_index(loggers_ref, 1);
  REQUIRE(console != nullptr);

  const auto& console_ref = *console;
  REQUIRE(examples::dist(console_ref) == 3);

  {
    const auto name = console_ref.get_as<string>(NAME);
    REQUIRE(static_cast<bool>(name));
    REQUIRE(*name == "console");

    const auto pattern = console_ref.get_as<string>(names::PATTERN);
    REQUIRE(static_cast<bool>(pattern));
    REQUIRE(*pattern == "easy");

    const auto level = console_ref.get_as<string>(LEVEL);
    REQUIRE(static_cast<bool>(level));
    REQUIRE(*level == "critical");
  }
}

TEST_CASE("Save logger to file overwriting existing file", "[save_logger_to_file_overwrite]")
{

  spdlog::drop_all();
  const auto logger = spdlog::stdout_logger_mt("console");
  logger->set_level(level_enum::err);

  const auto  tmp_file      = examples::get_simple_console_logger_conf_tmp_file();
  const auto& tmp_file_path = tmp_file.get_file_path();

  // true to overwrite the file completely
  spdlog_setup::save_logger_to_file(logger, tmp_file_path, true);

  const auto config = cpptoml::parse_file(tmp_file_path);
  REQUIRE(config != nullptr);

  // patterns

  const auto patterns = config->get_table_array(PATTERN_TABLE);
  REQUIRE(patterns == nullptr);

  // loggers

  const auto loggers = config->get_table_array(LOGGER_TABLE);
  REQUIRE(loggers != nullptr);

  const auto& loggers_ref = *loggers;
  REQUIRE(examples::dist(loggers_ref) == 1);

  const auto& console = examples::get_index(loggers_ref, 0);
  REQUIRE(console != nullptr);

  const auto& console_ref = *console;
  REQUIRE(examples::dist(console_ref) == 2);

  const auto name = console_ref.get_as<string>(NAME);
  REQUIRE(static_cast<bool>(name));
  REQUIRE(*name == "console");

  const auto level = console_ref.get_as<string>(LEVEL);
  REQUIRE(static_cast<bool>(level));
  REQUIRE(*level == "err");
}

TEST_CASE("Delete logger from file simple", "[delete_logger_in_file_simple]")
{
  spdlog::drop_all();

  const auto  tmp_file      = examples::get_simple_console_logger_conf_tmp_file();
  const auto& tmp_file_path = tmp_file.get_file_path();

  {
    const auto entry_deleted = spdlog_setup::delete_logger_in_file("not-console", tmp_file_path);

    REQUIRE(entry_deleted);

    const auto config = cpptoml::parse_file(tmp_file_path);
    REQUIRE(config != nullptr);

    // patterns

    const auto patterns = config->get_table_array(PATTERN_TABLE);
    REQUIRE(patterns != nullptr);

    const auto& patterns_ref = *patterns;
    REQUIRE(examples::dist(patterns_ref) == 1);

    const auto& pattern = examples::get_index(patterns_ref, 0);
    REQUIRE(pattern != nullptr);

    const auto& pattern_ref = *pattern;

    {
      const auto name = pattern_ref.get_as<string>(NAME);
      REQUIRE(static_cast<bool>(name));
      REQUIRE(*name == "easy");

      const auto value = pattern_ref.get_as<string>(VALUE);
      REQUIRE(static_cast<bool>(value));
      REQUIRE(*value == "%L: %v");
    }

    // loggers

    const auto loggers = config->get_table_array(LOGGER_TABLE);
    REQUIRE(loggers != nullptr);

    const auto& loggers_ref = *loggers;
    REQUIRE(examples::dist(loggers_ref) == 1);

    const auto& console = examples::get_index(loggers_ref, 0);
    REQUIRE(console != nullptr);

    const auto& console_ref = *console;
    REQUIRE(examples::dist(console_ref) == 3);

    {
      const auto name = console_ref.get_as<string>(NAME);
      REQUIRE(static_cast<bool>(name));
      REQUIRE(*name == "console");

      const auto pattern = console_ref.get_as<string>(names::PATTERN);
      REQUIRE(static_cast<bool>(pattern));
      REQUIRE(*pattern == "easy");

      const auto level = console_ref.get_as<string>(LEVEL);
      REQUIRE(static_cast<bool>(level));
      REQUIRE(*level == "trace");
    }
  }

  {
    const auto entry_deleted = spdlog_setup::delete_logger_in_file("no-such-thing", tmp_file_path);

    REQUIRE(!entry_deleted);

    const auto config = cpptoml::parse_file(tmp_file_path);
    REQUIRE(config != nullptr);

    const auto loggers = config->get_table_array(LOGGER_TABLE);
    REQUIRE(loggers != nullptr);

    const auto& loggers_ref = *loggers;
    REQUIRE(examples::dist(loggers_ref) == 1);
  }

  {
    const auto entry_deleted = spdlog_setup::delete_logger_in_file("console", tmp_file_path);

    REQUIRE(entry_deleted);

    const auto config = cpptoml::parse_file(tmp_file_path);
    REQUIRE(config != nullptr);

    const auto loggers = config->get_table_array(LOGGER_TABLE);
    REQUIRE(loggers == nullptr);
  }

  // opening the file without any loggers will throw an exception

  REQUIRE_THROWS_AS(spdlog_setup::delete_logger_in_file("console", tmp_file_path), setup_error);
}

TEST_CASE("Delete logger from empty file", "[delete_logger_in_file_empty]")
{
  spdlog::drop_all();

  const auto  tmp_file      = examples::tmp_file();
  const auto& tmp_file_path = tmp_file.get_file_path();

  // opening the file without any loggers will throw an exception

  REQUIRE_THROWS_AS(spdlog_setup::delete_logger_in_file("any-log", tmp_file_path), setup_error);
}

TEST_CASE("Check templating", "[check_templating]")
{
  REQUIRE(render("", {{}}) == "");
  REQUIRE(render("abc", {{}}) == "abc");
  REQUIRE(render("{{ a }}", {{"a", "Alpha"}}) == "Alpha");

  REQUIRE(render("{{ a }}{{bb}}{{ ccc}}{{dddd }}", {
                                                       {"a", "Alpha"},
                                                       {"bb", "Beta"},
                                                       {"ccc", "Ceta"},
                                                       {"dddd", "Delta"},
                                                   }) == "AlphaBetaCetaDelta");

  REQUIRE(render("{{\"Hello\"}} {{ \"{{\" }} {{\"}}\" }}", {{}}) == "Hello {{ }}");

  REQUIRE(render("a{{b}}cd{{e}}f{{\"g\"}}hij{{ k}}{{l }}) ({{ b }}{{e}}", {
                                                                              {"b", "BBB"},
                                                                              {"k", "KKK"},
                                                                              {"l", "LLL"},
                                                                          }) == "aBBBcdfghijKKKLLL) (BBB");
}
