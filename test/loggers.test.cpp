/**
 * Unit tests implementation.
 * @author Chen Weiguang
 * @version 0.3.3-pre
 */

#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <spdlog_setup/spdlog_setup.hpp>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <utility>

namespace spdlog_setup::details {

static constexpr auto TEST_LOGGER_NAME = "default";
static constexpr auto TEST_SINK_NAME   = "default";

inline auto
generate_stdout_sink_st() -> std::shared_ptr<cpptoml::table>
{
  namespace names = spdlog_setup::details::names;

  auto sink_table = cpptoml::make_table();
  sink_table->insert(names::TYPE, std::string("stdout_sink_st"));
  return std::move(sink_table);
}

inline auto
generate_simple_default_logger_table() -> std::shared_ptr<cpptoml::table>
{
  namespace names = spdlog_setup::details::names;

  auto logger_table = cpptoml::make_table();
  logger_table->insert(names::NAME, std::string(TEST_LOGGER_NAME));
  logger_table->insert(names::SINKS, cpptoml::make_array());
  return std::move(logger_table);
}

inline auto
generate_simple_default_logger_with_properties_table() -> std::shared_ptr<cpptoml::table>
{
  namespace details = spdlog_setup::details;
  namespace names   = details::names;

  auto err_str  = details::level_to_str(spdlog::level::err);
  auto crit_str = details::level_to_str(spdlog::level::critical);

  auto logger_table = cpptoml::make_table();
  logger_table->insert(names::NAME, std::string(TEST_LOGGER_NAME));
  logger_table->insert(names::SINKS, cpptoml::make_array());
  logger_table->insert(names::LEVEL, err_str);
  logger_table->insert(names::FLUSH_LEVEL, crit_str);
  return std::move(logger_table);
}

inline auto
generate_simple_sync_logger_table() -> std::shared_ptr<cpptoml::table>
{
  namespace names = spdlog_setup::details::names;

  auto logger_table = cpptoml::make_table();
  logger_table->insert(names::NAME, std::string(TEST_LOGGER_NAME));
  logger_table->insert(names::TYPE, names::SYNC);
  logger_table->insert(names::SINKS, cpptoml::make_array());
  return std::move(logger_table);
}

inline auto
generate_simple_async_logger_table() -> std::shared_ptr<cpptoml::table>
{
  namespace names = spdlog_setup::details::names;

  auto logger_table = cpptoml::make_table();
  logger_table->insert(names::NAME, std::string(TEST_LOGGER_NAME));
  logger_table->insert(names::TYPE, names::ASYNC);
  logger_table->insert(names::SINKS, cpptoml::make_array());
  return std::move(logger_table);
}

inline auto
generate_global_async_logger_table() -> std::shared_ptr<cpptoml::table>
{
  namespace names = spdlog_setup::details::names;

  auto logger_table = cpptoml::make_table();
  logger_table->insert(names::NAME, std::string(TEST_LOGGER_NAME));
  logger_table->insert(names::TYPE, names::ASYNC);
  logger_table->insert(names::SINKS, cpptoml::make_array());
  return std::move(logger_table);
}

inline auto
generate_invalid_sync_logger_table() -> std::shared_ptr<cpptoml::table>
{
  namespace names = spdlog_setup::details::names;

  auto logger_table = cpptoml::make_table();
  logger_table->insert(names::NAME, std::string(TEST_LOGGER_NAME));
  logger_table->insert(names::TYPE, "xxx");
  logger_table->insert(names::SINKS, cpptoml::make_array());
  return std::move(logger_table);
}

inline auto
generate_async_overflow_policy_block_logger_table() -> std::shared_ptr<cpptoml::table>
{
  namespace names = spdlog_setup::details::names;

  auto logger_table = cpptoml::make_table();
  logger_table->insert(names::NAME, std::string(TEST_LOGGER_NAME));
  logger_table->insert(names::TYPE, names::ASYNC);
  logger_table->insert(names::OVERFLOW_POLICY, names::BLOCK);
  logger_table->insert(names::SINKS, cpptoml::make_array());
  return std::move(logger_table);
}

inline auto
generate_async_overflow_policy_overrun_oldest_logger_table() -> std::shared_ptr<cpptoml::table>
{
  namespace names = spdlog_setup::details::names;

  auto logger_table = cpptoml::make_table();
  logger_table->insert(names::NAME, std::string(TEST_LOGGER_NAME));
  logger_table->insert(names::TYPE, names::ASYNC);
  logger_table->insert(names::OVERFLOW_POLICY, names::OVERRUN_OLDEST);
  logger_table->insert(names::SINKS, cpptoml::make_array());
  return std::move(logger_table);
}

inline auto
generate_invalid_async_overflow_policy_logger_table() -> std::shared_ptr<cpptoml::table>
{
  namespace names = spdlog_setup::details::names;

  auto logger_table = cpptoml::make_table();
  logger_table->insert(names::NAME, std::string(TEST_LOGGER_NAME));
  logger_table->insert(names::TYPE, names::ASYNC);
  logger_table->insert(names::OVERFLOW_POLICY, "xxx");
  logger_table->insert(names::SINKS, cpptoml::make_array());
  return std::move(logger_table);
}

inline auto
generate_simple_logger_with_sink_table() -> std::shared_ptr<cpptoml::table>
{
  namespace names = spdlog_setup::details::names;

  auto logger_table = cpptoml::make_table();
  logger_table->insert(names::NAME, std::string(TEST_LOGGER_NAME));

  auto sinks = cpptoml::make_array();
  sinks->push_back(std::string(TEST_SINK_NAME));
  logger_table->insert(names::SINKS, std::move(sinks));

  return std::move(logger_table);
}

const std::unordered_map<std::string, std::shared_ptr<spdlog::sinks::sink>>          EMPTY_SINKS_MAP;
const std::unordered_map<std::string, std::string>                                   EMPTY_PATTERNS_MAP;
const std::unordered_map<std::string, std::shared_ptr<spdlog::details::thread_pool>> EMPTY_THREAD_POOLS_MAP;
const cpptoml::option<std::string>                                                   EMPTY_GLOBAL_PATTERN_OPT;

TEST_CASE("Parse default logger", "[parse_simple_default_logger]")
{
  const auto logger =
      spdlog_setup::details::setup_logger(generate_simple_default_logger_table(), EMPTY_SINKS_MAP, EMPTY_PATTERNS_MAP,
                                          EMPTY_THREAD_POOLS_MAP, EMPTY_GLOBAL_PATTERN_OPT);

  REQUIRE(logger->name() == TEST_LOGGER_NAME);
  REQUIRE(typeid(*logger) == typeid(const spdlog::logger&));
}

TEST_CASE("Parse default logger with properties", "[parse_simple_default_logger_with_properties]")
{
  const auto logger =
      spdlog_setup::details::setup_logger(generate_simple_default_logger_with_properties_table(), EMPTY_SINKS_MAP,
                                          EMPTY_PATTERNS_MAP, EMPTY_THREAD_POOLS_MAP, EMPTY_GLOBAL_PATTERN_OPT);

  REQUIRE(logger->name() == TEST_LOGGER_NAME);
  REQUIRE(typeid(*logger) == typeid(const spdlog::logger&));
  REQUIRE(logger->level() == spdlog::level::err);
  REQUIRE(logger->flush_level() == spdlog::level::critical);
}

TEST_CASE("Parse sync logger", "[parse_simple_sync_logger]")
{
  const auto logger =
      spdlog_setup::details::setup_logger(generate_simple_sync_logger_table(), EMPTY_SINKS_MAP, EMPTY_PATTERNS_MAP,
                                          EMPTY_THREAD_POOLS_MAP, EMPTY_GLOBAL_PATTERN_OPT);

  REQUIRE(logger->name() == TEST_LOGGER_NAME);
  REQUIRE(typeid(*logger) == typeid(const spdlog::logger&));
}

TEST_CASE("Parse async logger", "[parse_simple_async_logger]")
{
  const auto logger =
      spdlog_setup::details::setup_logger(generate_simple_async_logger_table(), EMPTY_SINKS_MAP, EMPTY_PATTERNS_MAP,
                                          EMPTY_THREAD_POOLS_MAP, EMPTY_GLOBAL_PATTERN_OPT);

  REQUIRE(logger->name() == TEST_LOGGER_NAME);
  REQUIRE(typeid(*logger) == typeid(const spdlog::async_logger&));
}

TEST_CASE("Parse invalid sync logger", "[parse_invalid_sync_logger]")
{
  REQUIRE_THROWS_AS(spdlog_setup::details::setup_logger(generate_invalid_sync_logger_table(), EMPTY_SINKS_MAP,
                                                        EMPTY_PATTERNS_MAP, EMPTY_THREAD_POOLS_MAP,
                                                        EMPTY_GLOBAL_PATTERN_OPT),
                    spdlog_setup::setup_error);
}

TEST_CASE("Parse async overflow policy block logger", "[parse_simple_async_overflow_policy_block_logger]")
{
  const auto logger =
      spdlog_setup::details::setup_logger(generate_async_overflow_policy_block_logger_table(), EMPTY_SINKS_MAP,
                                          EMPTY_PATTERNS_MAP, EMPTY_THREAD_POOLS_MAP, EMPTY_GLOBAL_PATTERN_OPT);

  REQUIRE(logger->name() == TEST_LOGGER_NAME);
  REQUIRE(typeid(*logger) == typeid(const spdlog::async_logger&));
}

TEST_CASE("Parse async overflow policy overrun oldest logger",
          "[parse_simple_async_overflow_policy_overrun_oldest_logger]")
{
  const auto logger =
      spdlog_setup::details::setup_logger(generate_async_overflow_policy_overrun_oldest_logger_table(), EMPTY_SINKS_MAP,
                                          EMPTY_PATTERNS_MAP, EMPTY_THREAD_POOLS_MAP, EMPTY_GLOBAL_PATTERN_OPT);

  REQUIRE(logger->name() == TEST_LOGGER_NAME);
  REQUIRE(typeid(*logger) == typeid(const spdlog::async_logger&));
}

TEST_CASE("Parse invalid async overflow policy logger", "[parse_invalid_async_overflow_policy_logger]")
{
  REQUIRE_THROWS_AS(spdlog_setup::details::setup_logger(generate_invalid_async_overflow_policy_logger_table(),
                                                        EMPTY_SINKS_MAP, EMPTY_PATTERNS_MAP, EMPTY_THREAD_POOLS_MAP,
                                                        EMPTY_GLOBAL_PATTERN_OPT),
                    spdlog_setup::setup_error);
}

TEST_CASE("Parse logger with sink", "[parse_logger_with_sink]")
{
  auto       sink = spdlog_setup::details::setup_sink(generate_stdout_sink_st());
  const auto sinks_map =
      std::unordered_map<std::string, std::shared_ptr<spdlog::sinks::sink>>{{TEST_SINK_NAME, std::move(sink)}};

  const auto logger =
      spdlog_setup::details::setup_logger(generate_simple_logger_with_sink_table(), sinks_map, EMPTY_PATTERNS_MAP,
                                          EMPTY_THREAD_POOLS_MAP, EMPTY_GLOBAL_PATTERN_OPT);

  REQUIRE(logger->name() == TEST_LOGGER_NAME);
  REQUIRE(logger->sinks()[0] == sinks_map.at(TEST_SINK_NAME));
}

TEST_CASE("Parse logger with missing sink", "[parse_logger_with_missing_sink]")
{
  auto       sink = spdlog_setup::details::setup_sink(generate_stdout_sink_st());
  const auto sinks_map =
      std::unordered_map<std::string, std::shared_ptr<spdlog::sinks::sink>>{{"xxx", std::move(sink)}};

  REQUIRE_THROWS_AS(spdlog_setup::details::setup_logger(generate_simple_logger_with_sink_table(), sinks_map,
                                                        EMPTY_PATTERNS_MAP, EMPTY_THREAD_POOLS_MAP,
                                                        EMPTY_GLOBAL_PATTERN_OPT),
                    spdlog_setup::setup_error);
}
} // namespace spdlog_setup::details
