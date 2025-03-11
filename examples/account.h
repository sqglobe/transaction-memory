#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <cstddef>

class Account {
public:
    Account(std::size_t current, std::size_t max);

public:
  bool withdraw(std::size_t amount);
  bool put(std::size_t amount);

private:
  std::size_t m_current;
  std::size_t m_max;
};


Account::Account(std::size_t current, std::size_t max): m_current(current), m_max(max) {}

bool Account::withdraw(std::size_t amount)
{
    if(m_current < amount){
        return false;
    }
    m_current -= amount;
    return true;
}

bool Account::put(std::size_t amount)
{
    if(m_current + amount >= m_max) {
        return false;
    }
    m_current += amount;
    return true;
}

#endif // ACCOUNT_H
