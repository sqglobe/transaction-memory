#ifndef TRANSACTIONAL_H
#define TRANSACTIONAL_H

#include "account.h"
#include <vector>
#include <stdexcept>

namespace transactional {

class Counter
{
public:
    int count()
    {
        synchronized
        {
            return i++;
        }
    }

private:
    int i = 0;
};

bool transfer(Account &from, std::size_t amountPerAccount, std::vector<Account> &to)
{
    const std::size_t total = amountPerAccount * to.size();
    // Start the transaction
    __transaction_atomic{
        if (!from.withdraw(total)) {
            // Rollback on error
            // Control flow after this point
            // goes directly to `return false;`
            // statement
            __transaction_cancel;
        }
        for (auto &account : to) {
            if (!account.put(amountPerAccount)) {
                // Rollback on error
                // Control flow after this point
                // goes directly to `return false;`
                // statement
                __transaction_cancel;
            }
        }
        // Return from the transaction success
        // The transaction is committed automatically
        return true;
    }
    return false;
}
}

#endif // TRANSACTIONAL_H
