#include "CarController.h"
#include "Car.h"

using namespace std;

int main(int argc, char* argv[])
{
	Car car;
	CarController carController(car, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << endl << "> ";

		if (!carController.HandleCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}

	return 0;
}