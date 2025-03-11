#ifndef ALTERNATIVES_H
#define ALTERNATIVES_H

#include "account.h"
#include <mutex>
#include <vector>

namespace alternatives {

static std::mutex GlobalMutex;

// Increase number in thread-safe way
// using mutex
class Counter
{
public:
    int count()
    {
        auto lock = std::lock_guard{m_mutex};
        return i++;
    }

private:
    std::mutex m_mutex;
    int i = 0;
};

bool transfer(Account &from, std::size_t amountPerAccount, std::vector<Account> &to)
{
    const std::size_t total = amountPerAccount * to.size();
    auto lock = std::lock_guard{GlobalMutex};

    // Make a temporary copy
    auto fromCopy = from;

    // Apply changes on the copy
    if(!fromCopy.withdraw(total)) {
        return false;
    }
    std::vector<Account> copies;
    copies.reserve(to.size());
    for(const auto &account: to){
        // Make a copy
        auto copy = account;
        // Apply changes on the copy
        if(!copy.put(amountPerAccount)) {
            return false;
        }
        copies.push_back(copy);
    }
    // All changes were applied without error
    // replace real object with copies
    to = copies;
    from = fromCopy;
    return true;
}

} // namespace alternatives
#endif // ALTERNATIVES_H
