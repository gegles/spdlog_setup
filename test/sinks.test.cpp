/**
 * Unit tests implementation.
 * @author Chen Weiguang
 * @version 0.3.3-pre
 */

#include <spdlog_setup/spdlog_setup.hpp>
#include <catch2/catch_test_macros.hpp>

inline auto
generate_stdout_sink_st() -> std::shared_ptr<cpptoml::table>
{
  namespace names = spdlog_setup::details::names;

  auto sink_table = cpptoml::make_table();
  sink_table->insert(names::TYPE, std::string("stdout_sink_st"));
  return std::move(sink_table);
}

inline auto
generate_stderr_sink_st() -> std::shared_ptr<cpptoml::table>
{
  namespace names = spdlog_setup::details::names;

  auto sink_table = cpptoml::make_table();
  sink_table->insert(names::TYPE, std::string("stderr_sink_st"));
  return std::move(sink_table);
}

inline auto
generate_stdout_sink_mt() -> std::shared_ptr<cpptoml::table>
{
  namespace names = spdlog_setup::details::names;

  auto sink_table = cpptoml::make_table();
  sink_table->insert(names::TYPE, std::string("stdout_sink_mt"));
  return std::move(sink_table);
}

inline auto
generate_stderr_sink_mt() -> std::shared_ptr<cpptoml::table>
{
  namespace names = spdlog_setup::details::names;

  auto sink_table = cpptoml::make_table();
  sink_table->insert(names::TYPE, std::string("stderr_sink_mt"));
  return std::move(sink_table);
}

using namespace spdlog_setup::details;

TEST_CASE("Parse stdout sink st", "[parse_generate_stdout_sink_st]")
{
  const auto sink = spdlog_setup::details::setup_sink(generate_stdout_sink_st());
  REQUIRE(typeid(*sink) == typeid(const spdlog::sinks::stdout_sink_st&));
}

TEST_CASE("Parse stderr sink st", "[parse_generate_stderr_sink_st]")
{
  const auto sink = spdlog_setup::details::setup_sink(generate_stderr_sink_st());
  REQUIRE(typeid(*sink) == typeid(const spdlog::sinks::stderr_sink_st&));
}

TEST_CASE("Parse stdout sink mt", "[parse_generate_stdout_sink_mt]")
{
  const auto sink = spdlog_setup::details::setup_sink(generate_stdout_sink_mt());
  REQUIRE(typeid(*sink) == typeid(const spdlog::sinks::stdout_sink_mt&));
}

TEST_CASE("Parse stderr sink mt", "[parse_generate_stderr_sink_mt]")
{
  const auto sink = spdlog_setup::details::setup_sink(generate_stderr_sink_mt());
  REQUIRE(typeid(*sink) == typeid(const spdlog::sinks::stderr_sink_mt&));
}
