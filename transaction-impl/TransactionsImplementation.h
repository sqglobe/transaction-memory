#pragma once

#include <array>
#include <stdexcept>

namespace transactional {
class Counter {
public:
  int count() {
    synchronized { return i++; }
  }

private:
  int i = 0;
};

template <std::size_t Size> class ArraySum {
public:
  ArraySum(std::array<int, Size> values, int max)
      : m_values(std::move(values)), m_max(max) {}

public:
  // For each element calculate sum of the array and
  // assign to the current element,
  // throw an exception if calculated number excied the limit
  // and rallback the operation
  void calculateNext() noexcept(false);

  std::array<int, Size> values() const;

  void resetValues(std::array<int, Size> values);

private:
  // Calculate sum of elements in the array.
  // Mark function as safe for transaction,
  // so it might be executed inside the transaction
  int sum() const transaction_safe;

private:
  std::array<int, Size> m_values;
  int m_max;
};

template <std::size_t Size>
void ArraySum<Size>::calculateNext() noexcept(false) {
  // start the transaction
  __transaction_atomic {
    for (auto &e : m_values) {
      int s = sum();
      if (s >= m_max) {
        // rollback the transaction
        __transaction_cancel;
        throw std::runtime_error("more than limit");
      }
      e = s;
    }
  }
}

template <std::size_t Size>
std::array<int, Size> ArraySum<Size>::values() const {
  __transaction_atomic { return m_values; }
}

template <std::size_t Size>
void ArraySum<Size>::resetValues(std::array<int, Size> values) {
  __transaction_atomic { m_values = std::move(values); }
}

template <std::size_t Size> int ArraySum<Size>::sum() const transaction_safe {
  int sum = 0;
  for (auto e : m_values) {
    sum += e;
  }
  return sum;
}

} // namespace transactional
