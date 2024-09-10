# Add library contained main primitives
add_library(mutex-impl INTERFACE)
target_sources(mutex-impl INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/MutexImplementation.h")
target_include_directories(mutex-impl INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

# Test for class `Counter`
add_executable(mutex-counter-test CounterTest.cpp)
target_link_libraries(mutex-counter-test PRIVATE mutex-impl test-configuration)

# Test for class `ArraySum`
add_executable(mutex-array-sum-test ArraySumTest.cpp)
target_link_libraries(mutex-array-sum-test PRIVATE mutex-impl test-configuration)
