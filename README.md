# Transaction Memory Example

This code provides an example of a transactional memory proposal as described in [n1613](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1613.pdf).

You can find the transactional memory implementation in the [examples/transactional.h](examples/transactional.h) file.

Another file, [examples/alternatives.h](examples/alternatives.h), contains the same classes but implemented with `std::mutex` for synchronization. This allows for performance comparison between the transactional and mutex-based implementations.

Folder [benchmarks](benchmarks) contains google benchmarks for both transactional and alternative approaches.

## Building

To build that project you need **gcc** compiler and **libitm** installed on you machine.
Other compilers haven't support for that proposal.
