cmake_minimum_required(VERSION 3.12)

project(transaction-memory LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(examples)

add_subdirectory(benchmarks)

