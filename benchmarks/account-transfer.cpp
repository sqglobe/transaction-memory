#include <benchmark/benchmark.h>
#include "alternatives.h"
#include "transactional.h"


#include <iostream>

long alternative_transfer() {
    auto main = Account{100000, 9000000};
    auto to = std::vector<Account>{{0, 9000},{0, 9000},{0, 9000},{0, 9000},{0, 9000},{0, 9000},{0, 9000},{0, 9000},{7000, 9000},{0, 9000},{0, 9000},{4000, 9000}};
    long res = false;
    for(int i = 0; i < 1000; ++i){
        res += alternatives::transfer(main, 9, to);
    }
    return res;
}

long transactional_transfer() {
    auto main = Account{100000, 9000000};
    auto to = std::vector<Account>{{0, 9000},{0, 9000},{0, 9000},{0, 9000},{0, 9000},{0, 9000},{0, 9000},{0, 9000},{7000, 9000},{0, 9000},{0, 9000},{4000, 9000}};
    long res = false;
    for(int i = 0; i < 1000; ++i){
        res += transactional::transfer(main, 9, to);
    }
    return res;
}

void transactional_transfer_benchmark(benchmark::State &state) {
    for (auto _ : state) {
        const auto res = transactional_transfer();
        // Prevent loop optimisation
        benchmark::DoNotOptimize(res);
    }
}

void alternative_transfer_benchmark(benchmark::State &state) {
    for (auto _ : state) {
        const auto res = alternative_transfer();
        // Prevent loop optimisation
        benchmark::DoNotOptimize(res);
    }
}

BENCHMARK(transactional_transfer_benchmark);
BENCHMARK(alternative_transfer_benchmark);
BENCHMARK_MAIN();
