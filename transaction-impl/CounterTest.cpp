#include "TestConfiguration.h"
#include "TransactionsImplementation.h"
#include <chrono>

int main() {
  {
    Timer timer;
    transactional::Counter counter;
    for (std::size_t i = 0; i < CountNumber; i++) {
      auto r = counter.count();
      if (i != r) {
        std::cerr << "Not equal" << std::endl;
      }
    }
  }
  return 0;
}
