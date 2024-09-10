# Look for library `itm` that contains required symbols
find_library(ITM
     NAMES itm itm.so libitm.so
     PATHS /usr/x86_64-linux-gnu/lib/ /usr/lib/x86_64-linux-gnu/)

# Add library contained main primitives implemented with transactional memory proposal
add_library(transaction-impl INTERFACE)
target_sources(transaction-impl INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/TransactionsImplementation.h")
target_include_directories(transaction-impl INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

target_compile_options(transaction-impl INTERFACE -fgnu-tm)
target_link_libraries(transaction-impl  INTERFACE ${ITM})

# Test for class `Counter`
add_executable(transaction-counter-test CounterTest.cpp)
target_link_libraries(transaction-counter-test PRIVATE transaction-impl test-configuration)

# Test for class `ArraySum`
add_executable(transaction-array-sum-test ArraySumTest.cpp)
target_link_libraries(transaction-array-sum-test PRIVATE transaction-impl test-configuration)
