cmake_minimum_required(VERSION 3.5)

project(transaction-memory LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Parameters required for testing
add_subdirectory(test-configuration)

# Classes implementation based on transaction memory proposal
add_subdirectory(transaction-impl)

# Implementation based on   mutexes
add_subdirectory(mutex-impl)

