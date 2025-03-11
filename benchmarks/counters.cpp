#include <benchmark/benchmark.h>
#include "alternatives.h"
#include "transactional.h"

long alternative_counter() {
    long var = 0;
    auto counter = alternatives::Counter{};
    for(int i = 0; i < 1000; ++i){
        var += counter.count();
    }
    return var;
}

long transactional_counter() {
    long var = 0;
    auto counter = transactional::Counter{};
    for(int i = 0; i < 1000; ++i){
        var += counter.count();
    }
    return var;
}

void transactional_counter_benchmark(benchmark::State &state) {
    for (auto _ : state) {
        const auto res = transactional_counter();
        // Prevent loop optimisation
        benchmark::DoNotOptimize(res);
    }
}

void alternative_counter_benchmark(benchmark::State &state) {
    for (auto _ : state) {
        const auto res = alternative_counter();
        // Prevent loop optimisation
        benchmark::DoNotOptimize(res);
    }
}

BENCHMARK(transactional_counter_benchmark);
BENCHMARK(alternative_counter_benchmark);
BENCHMARK_MAIN();
