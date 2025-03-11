find_package(benchmark REQUIRED)

# Benchmark for counter
add_executable(counters counters.cpp)
target_link_libraries(counters examples benchmark::benchmark)

# Becnhmark for account transfer function
add_executable(account-transfer account-transfer.cpp)
target_link_libraries(account-transfer examples benchmark::benchmark)
