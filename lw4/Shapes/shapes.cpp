#include <iostream>
#include "CController.h"

int main()
{
	CController controller(std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		try
		{
			std::cout << "> ";
			controller.HandleCommand();
		}
		catch (std::exception const& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	try
	{
		controller.GetShapesInfo();
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}