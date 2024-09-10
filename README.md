# Transaction Memory Example

This code provides an example of a transactional memory proposal as described in [n1613](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1613.pdf).

You can find the transactional memory implementation in the [transaction-impl](transaction-impl) folder. This folder also contains several `.cpp` files with usage examples, which can be executed for time measurement.

Another folder, [mutex-impl](mutex-impl), contains the same classes but implemented with `std::mutex` for synchronization. This allows for performance comparison between the transactional and mutex-based implementations.

The last folder, [test-configuration](test-configuration), includes settings and initial data needed for measurement, such as the number of iterations or the timer class used to calculate the elapsed time.

## Building

To build that project you need **gcc** compiler and **libitm** installed on you machine.
Other compilers haven't support for that proposal.
