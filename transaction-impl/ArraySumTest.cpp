#include "TestConfiguration.h"
#include "TransactionsImplementation.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>

int main() {
  {
    Timer timer;
    transactional::ArraySum sum(Array, MaxArrayNumber);

    auto print = [](const auto &sum) {
      const auto values = sum.values();
      std::copy(values.cbegin(), values.cend(),
                std::ostream_iterator<int>(std::cout, ","));
      std::cout << std::endl;
    };

    for (std::size_t i = 0; i < CountNumber; i++) {
      try {
        sum.calculateNext();
      } catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
        print(sum);
        sum.resetValues(Array);
      }
    }
  }
  return 0;
}
