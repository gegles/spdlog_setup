/**
 * Unit tests implementation.
 * @author Chen Weiguang
 * @version 0.3.3-pre
 */

#include <spdlog_setup/spdlog_setup.hpp>
#include <catch2/catch_test_macros.hpp>
#include <cpptoml.h>

static constexpr auto TEST_THREAD_POOL_NAME = "default";

inline auto
generate_global_thread_pool() -> std::shared_ptr<cpptoml::table>
{
  namespace names = spdlog_setup::details::names;

  auto global_thread_inner_pool_table = cpptoml::make_table();
  global_thread_inner_pool_table->insert(names::QUEUE_SIZE, size_t(1234));
  global_thread_inner_pool_table->insert(names::NUM_THREADS, size_t(9));

  auto conf = cpptoml::make_table();
  conf->insert(names::GLOBAL_THREAD_POOL_TABLE, std::move(global_thread_inner_pool_table));

  return std::move(conf);
}

inline auto
generate_simple_thread_pool() -> std::shared_ptr<cpptoml::table>
{
  namespace names = spdlog_setup::details::names;

  auto thread_pool_table_array = cpptoml::make_table_array();

  auto thread_pool_table = cpptoml::make_table();
  thread_pool_table->insert(names::NAME, TEST_THREAD_POOL_NAME);
  thread_pool_table->insert(names::QUEUE_SIZE, size_t(1234));
  thread_pool_table->insert(names::NUM_THREADS, size_t(9));
  thread_pool_table_array->push_back(std::move(thread_pool_table));

  auto conf = cpptoml::make_table();
  conf->insert(names::THREAD_POOL_TABLE, std::move(thread_pool_table_array));

  return std::move(conf);
}

inline auto
generate_multiple_thread_pools(const size_t count) -> std::shared_ptr<cpptoml::table>
{
  namespace names = spdlog_setup::details::names;

  auto thread_pool_table_array = cpptoml::make_table_array();

  for (size_t i = 0; i < count; ++i) {
    auto thread_pool_table = cpptoml::make_table();
    thread_pool_table->insert(names::NAME, TEST_THREAD_POOL_NAME + std::to_string(i));
    thread_pool_table->insert(names::QUEUE_SIZE, size_t(1234));
    thread_pool_table->insert(names::NUM_THREADS, size_t(9));
    thread_pool_table_array->push_back(std::move(thread_pool_table));
  }

  auto conf = cpptoml::make_table();
  conf->insert(names::THREAD_POOL_TABLE, std::move(thread_pool_table_array));

  return std::move(conf);
}

inline auto
generate_invalid_no_name_thread_pool() -> std::shared_ptr<cpptoml::table>
{
  namespace names = spdlog_setup::details::names;

  auto thread_pool_table_array = cpptoml::make_table_array();

  auto thread_pool_table = cpptoml::make_table();
  thread_pool_table->insert(names::QUEUE_SIZE, size_t(1234));
  thread_pool_table->insert(names::NUM_THREADS, size_t(9));
  thread_pool_table_array->push_back(std::move(thread_pool_table));

  auto conf = cpptoml::make_table();
  conf->insert(names::THREAD_POOL_TABLE, std::move(thread_pool_table_array));

  return std::move(conf);
}

inline auto
generate_invalid_no_queue_size_thread_pool() -> std::shared_ptr<cpptoml::table>
{
  namespace names = spdlog_setup::details::names;

  auto thread_pool_table_array = cpptoml::make_table_array();

  auto thread_pool_table = cpptoml::make_table();
  thread_pool_table->insert(names::NAME, TEST_THREAD_POOL_NAME);
  thread_pool_table->insert(names::NUM_THREADS, size_t(9));
  thread_pool_table_array->push_back(std::move(thread_pool_table));

  auto conf = cpptoml::make_table();
  conf->insert(names::THREAD_POOL_TABLE, std::move(thread_pool_table_array));

  return std::move(conf);
}

inline auto
generate_invalid_no_num_threads_thread_pool() -> std::shared_ptr<cpptoml::table>
{
  namespace names = spdlog_setup::details::names;

  auto thread_pool_table_array = cpptoml::make_table_array();

  auto thread_pool_table = cpptoml::make_table();
  thread_pool_table->insert(names::NAME, TEST_THREAD_POOL_NAME);
  thread_pool_table->insert(names::QUEUE_SIZE, size_t(1234));
  thread_pool_table_array->push_back(std::move(thread_pool_table));

  auto conf = cpptoml::make_table();
  conf->insert(names::THREAD_POOL_TABLE, std::move(thread_pool_table_array));

  return std::move(conf);
}

TEST_CASE("Parse global thread pool", "[parse_global_thread_pool]")
{
  // Cannot test queue size and thread count as they are not exposed publicly
  // Can only test that the thread pool was changed to another instance
  const auto original = spdlog::thread_pool();

  const auto thread_pools = spdlog_setup::details::setup_thread_pools(generate_global_thread_pool());
  const auto modified     = spdlog::thread_pool();

  REQUIRE(original != modified);
  REQUIRE(thread_pools.empty());
}

TEST_CASE("Parse simple thread pool", "[parse_simple_thread_pool]")
{
  // No way to test non-global thread pool from spdlog sadly
  const auto thread_pools = spdlog_setup::details::setup_thread_pools(generate_simple_thread_pool());

  REQUIRE(thread_pools.size() == 1);
}

TEST_CASE("Parse multiple thread pools", "[parse_multiple_thread_pools]")
{
  const auto thread_pools = spdlog_setup::details::setup_thread_pools(generate_multiple_thread_pools(10));

  REQUIRE(thread_pools.size() == 10);
}

TEST_CASE("Parse invalid no name thread pool", "[parse_invalid_no_name_thread_pool]")
{
  REQUIRE_THROWS_AS(spdlog_setup::details::setup_thread_pools(generate_invalid_no_name_thread_pool()),
                    spdlog_setup::setup_error);
}

TEST_CASE("Parse invalid no queue size thread pool", "[parse_invalid_no_queue_size_thread_pool]")
{
  REQUIRE_THROWS_AS(spdlog_setup::details::setup_thread_pools(generate_invalid_no_queue_size_thread_pool()),
                    spdlog_setup::setup_error);
}

TEST_CASE("Parse invalid no num threads thread pool", "[parse_invalid_no_num_threads_thread_pool]")
{
  REQUIRE_THROWS_AS(spdlog_setup::details::setup_thread_pools(generate_invalid_no_num_threads_thread_pool()),
                    spdlog_setup::setup_error);
}
