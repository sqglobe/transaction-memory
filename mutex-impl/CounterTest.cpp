#include "MutexImplementation.h"
#include "TestConfiguration.h"
#include <chrono>

int main() {
  {
    Timer timer;
    mutexes::Counter counter;
    for (std::size_t i = 0; i < CountNumber; i++) {
      auto r = counter.count();
      if (i != r) {
        std::cerr << "Not equal" << std::endl;
      }
    }
  }
  return 0;
}
