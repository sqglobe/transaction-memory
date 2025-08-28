#include "alternatives.h"
#include "transactional.h"
#include <benchmark/benchmark.h>
#include <thread>
#include <vector>

constexpr std::size_t ThreadsNumber = 50;

void alternative_transfer() {
  auto main = Account{100000, 9000000};
  auto to = std::vector<Account>{
      {0, 9000}, {0, 9000}, {0, 9000},    {0, 9000}, {0, 9000}, {0, 9000},
      {0, 9000}, {0, 9000}, {7000, 9000}, {0, 9000}, {0, 9000}, {4000, 9000}};
  long res = false;
  for (int i = 0; i < 1000; ++i) {
    res += alternatives::transfer(main, 9, to);
  }
  // Prevent loop optimisation
  benchmark::DoNotOptimize(res);
}

void transactional_transfer() {
  auto main = Account{100000, 9000000};
  auto to = std::vector<Account>{
      {0, 9000}, {0, 9000}, {0, 9000},    {0, 9000}, {0, 9000}, {0, 9000},
      {0, 9000}, {0, 9000}, {7000, 9000}, {0, 9000}, {0, 9000}, {4000, 9000}};
  long res = false;
  for (int i = 0; i < 1000; ++i) {
    res += transactional::transfer(main, 9, to);
  }
  // Prevent loop optimisation
  benchmark::DoNotOptimize(res);
}

void transactional_transfer_benchmark(benchmark::State &state) {
  for (auto _ : state) {
    transactional_transfer();
  }
}

void transactional_multithreaded_transfer_benchmark(benchmark::State &state) {
  for (auto _ : state) {
    std::vector<std::jthread> threads;
    for (std::size_t i = 0; i < ThreadsNumber; ++i) {
      threads.emplace_back(transactional_transfer);
    }
  }
}

void alternative_transfer_benchmark(benchmark::State &state) {
  for (auto _ : state) {
    alternative_transfer();
  }
}

void alternative__multithreaded_transfer_benchmark(benchmark::State &state) {
  for (auto _ : state) {
    std::vector<std::jthread> threads;
    for (std::size_t i = 0; i < ThreadsNumber; ++i) {
      threads.emplace_back(alternative_transfer);
    }
  }
}

BENCHMARK(transactional_transfer_benchmark);
BENCHMARK(alternative_transfer_benchmark);

BENCHMARK(transactional_multithreaded_transfer_benchmark);
BENCHMARK(alternative__multithreaded_transfer_benchmark);
BENCHMARK_MAIN();
