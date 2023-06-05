#include "pch.h"
#include "vector.h"

TEST_CASE("ProcessVector: Vector with no numbers")
{
	std::vector<float> v = {};
	std::vector<float> vExpected = {};
	ProcessVector(v);
	CHECK_THAT(v, Catch::Approx(vExpected).epsilon(1.e-3f));
}

TEST_CASE("ProcessVector: Vector with numbers")
{
	std::vector<float> v = { 2.0f, 3.0f };
	std::vector<float> vExpected = { 3.0f, 4.5f };
	ProcessVector(v);
	CHECK_THAT(v, Catch::Approx(vExpected).epsilon(1.e-3f));
}

TEST_CASE("ProcessVector: Vector with the same numbers")
{
	std::vector<float> v = { 2.5f, 2.5f, 2.5f, 2.5f };
	std::vector<float> vExpected = { 2.5f, 2.5f, 2.5f, 2.5f };
	ProcessVector(v);
	CHECK_THAT(v, Catch::Approx(vExpected).epsilon(1.e-3f));
}

TEST_CASE("ProcessVector: Vector with zeros")
{
	std::vector<float> v = { 0, 0, 0, 0 };
	std::vector<float> vExpected = { 0.0f, 0.0f, 0.0f, 0.0f };
	ProcessVector(v);
	CHECK_THAT(v, Catch::Approx(vExpected).epsilon(1.e-3f));
}