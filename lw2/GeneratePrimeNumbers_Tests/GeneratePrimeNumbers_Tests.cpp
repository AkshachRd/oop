#include "..\..\catch2\catch.hpp"
#include "..\GeneratePrimeNumbers\GeneratePrimeNumbers.h"
#include <ctime>

TEST_CASE("GeneratePrimeNumbersSet: check time and quantity prime nums")
{
	auto start = clock();
	std::set<int> primeNums = GeneratePrimeNumbersSet(100000000);
	auto end = clock();
	REQUIRE((end - start) / 1000 < 12);
	REQUIRE(primeNums.size() == 5761455);
}

TEST_CASE("GeneratePrimeNumbersSet: check prime nums if entered < 2")
{
	std::set<int> primeNums = GeneratePrimeNumbersSet(1);
	REQUIRE(primeNums.size() == 0);
};

TEST_CASE("Simple test")
{
	std::set<int> primeNums = GeneratePrimeNumbersSet(15);
	std::set<int> trueResult({ 2, 3, 5, 7, 11, 13 });
	REQUIRE(primeNums == trueResult);
};