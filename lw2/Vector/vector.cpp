#include <iostream>
#include <vector>
#include <algorithm>
#include "vector.h"

int main()
{
	std::vector<float> inputVector;

	if (!ParseVector(std::cin, inputVector))
	{
		std::cout << "Invalid input data or empty input" << std::endl;
		return 1;
	}

	// Multiple every vector element by max element and divide every vector element by min element
	if (!ProcessVector(inputVector))
	{
		return 1;
	}

	// in vec funcs
	// Vector sorting
	std::sort(inputVector.begin(), inputVector.end());

	// Copying vector to the output
	copy(inputVector.begin(), inputVector.end(), std::ostream_iterator<float>(std::cout, " "));

	return 0;
}