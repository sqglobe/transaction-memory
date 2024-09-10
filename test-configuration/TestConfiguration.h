#pragma once

#include <array>
#include <chrono>
#include <iostream>

constexpr std::size_t CountNumber = 200'000;
constexpr int MaxArrayNumber = 5000;
constexpr auto Array = std::array{0, 1, 1, 1, 0, 0, 0, 0, 1};
class Timer{
public:
    Timer(Timer&) = delete;
    Timer(Timer &&) = delete;
    Timer& operator=(Timer&) = delete;
    Timer& operator=(Timer&&) = delete;
public:
    Timer(): m_begin(std::chrono::steady_clock::now()){}
    ~Timer() {
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cerr << "Time difference = "
                  << std::chrono::duration<double, std::milli>(end - m_begin)
                         .count()
                  << "[ms]" << std::endl;
    }
private:
    std::chrono::steady_clock::time_point m_begin;
};
