#include <vector>
#include <iostream>
#include <algorithm>
#include "vector.h"

bool ParseVector(std::istream& inStrm, std::vector<float>& vec)
{
	float num = 0.f;

	while (inStrm >> num && !inStrm.eof())
	{
		vec.push_back(num);
	}

	if (inStrm.eof())
	{
		return false;
	}

	return true;
}

bool ProcessVector(std::vector<float>& vec)
{
	if (vec.empty())
	{
		return true;
	}

	//std::cout << "min = " << *min << ", max = " << *max << '\n';
	//float max = *std::max_element(std::begin(vec), std::end(vec));
	//float min = *std::min_element(std::begin(vec), std::end(vec));
	//std::for_each(vec.begin(), vec.end(), [max, min](float& n) { n = n * *max / *min; });

	//minmax_element
	const auto minmax = std::minmax_element(std::begin(vec), std::end(vec));
	float min = *minmax.first;
	float max = *minmax.second;
	if (min == 0)
	{
		return false;
	}
	//transform
	std::transform(vec.begin(), vec.end(), vec.begin(), [max, min](float n) -> float { return n * max / min; });

	return true;
}