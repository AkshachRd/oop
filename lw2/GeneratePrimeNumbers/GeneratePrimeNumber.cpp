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
    // ���� ����� i �������� �������, �� ��� ��� ������� �����, ������� ������ ��� ����� i^2,
    // ��� ������ ���� �������� ��� ��������� ����� ����� � ���������
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