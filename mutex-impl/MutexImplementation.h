#pragma once

#include <array>
#include <mutex>

namespace mutexes {

// Increase number in thread-safe way
// using mutex
class Counter {
public:
  int count() {
    auto lock = std::lock_guard{m_mutex};
    return i++;
  }

private:
  std::mutex m_mutex;
  int i = 0;
};

// Calculate sum of the elements in array
template <std::size_t Size> class ArraySum {
public:
  ArraySum(std::array<int, Size> values, int max)
      : m_values(std::move(values)), m_max(max) {}

public:
  // For each element calculate sum of the array and
  // assign to the current element,
  // throw an exception if calculated number excied the limit
  // and rallback the operation
  void calculateNext() noexcept(false) {
    auto lock = std::lock_guard{m_mutex};
    auto copy = m_values;
    for (auto &e : copy) {
      int s = sum();
      if (s >= m_max) {
        throw std::runtime_error("more than limit");
      }
      e = s;
    }
    m_values = copy;
  }

  std::array<int, Size> values() const {
    auto lock = std::lock_guard{m_mutex};
    return m_values;
  }

  void resetValues(std::array<int, Size> values) {
    auto lock = std::lock_guard{m_mutex};
    m_values = std::move(values);
  }

private:
  int sum() const {
    int sum = 0;
    for (auto e : m_values) {
      sum += e;
    }
    return sum;
  }

private:
  mutable std::mutex m_mutex;
  std::array<int, Size> m_values;
  int m_max;
};

} // namespace mutexes
