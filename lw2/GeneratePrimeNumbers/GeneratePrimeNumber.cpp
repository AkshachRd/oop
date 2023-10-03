#include "GeneratePrimeNumbers.h"

void RemoveMultiples(std::vector<bool>& sieve, int num)
{
    for (int j = 3 * num; j < sieve.size(); j += 2 * num)
    {
        sieve[j] = false;
    }
};

void RemoveEven(std::vector<bool>& sieve)
{
    for (int i = 4; i < sieve.size(); i += 2)
    {
        sieve[i] = false;
    }
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
    std::set<int> primeNums;

    if (upperBound < 2)
    {
        return primeNums;
    }

    primeNums.insert(2);

    std::vector<bool> sieve(upperBound + 1, true);

    RemoveEven(sieve);

    int sqrtUpperBound = (int)sqrt(upperBound);
    // если число i является простым, то все его кратные числа, которые меньше или равны i^2,
    // уже должны быть помечены как составные числа ранее в алгоритме
    for (int i = 3; i <= upperBound; i += 2)
    {
        if (!sieve[i])
        {
            continue;
        }

        primeNums.insert(i);

        if (i <= sqrtUpperBound)
        {
            RemoveMultiples(sieve, i);
        }
    }

    return primeNums;
}