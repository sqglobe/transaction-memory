#include "alternatives.h"
#include "transactional.h"
#include <benchmark/benchmark.h>
#include <future>
#include <numeric>
#include <thread>
#include <vector>

constexpr std::size_t ThreadsNumber = 50;

void count(auto &counter, int iterations) {
  long var = 0;
  for (int i = 0; i < iterations; ++i) {
    var += counter.count();
  }
  // Prevent loop optimisation
  benchmark::DoNotOptimize(var);
}

void count_multithreaded(auto &counter, int iterations,
                         std::size_t threadsNumber) {
  std::vector<std::jthread> threads;
  for (std::size_t i = 0; i < threadsNumber; ++i) {
    auto task = std::packaged_task<long()>();
    threads.emplace_back(
        [&counter, iterations] { count(counter, iterations); });
  }
}

void transactional_multithread_counter_benchmark(benchmark::State &state) {
  for (auto _ : state) {
    auto counter = transactional::Counter{};

    count_multithreaded(counter, 1000, ThreadsNumber);
  }
}

void alternative_multithread_counter_benchmark(benchmark::State &state) {
  for (auto _ : state) {
    auto counter = alternatives::Counter{};

    count_multithreaded(counter, 1000, ThreadsNumber);
  }
}

void transactional_single_thread_counter_benchmark(benchmark::State &state) {
  for (auto _ : state) {
    auto counter = transactional::Counter{};
    count(counter, 1000);
  }
}

void alternative_single_thread_counter_benchmark(benchmark::State &state) {
  for (auto _ : state) {
    auto counter = alternatives::Counter{};
    count(counter, 1000);
  }
}

BENCHMARK(transactional_single_thread_counter_benchmark);
BENCHMARK(alternative_single_thread_counter_benchmark);

BENCHMARK(transactional_multithread_counter_benchmark);
BENCHMARK(alternative_multithread_counter_benchmark);
BENCHMARK_MAIN();
