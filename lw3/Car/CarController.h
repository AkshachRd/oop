#include "Car.h"
#include <map>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

class CarController
{
public:
	CarController(Car& car, std::istream& input, std::ostream& output);

	bool HandleCommand();
private:
	bool Info(std::istream& args);
	bool EngineOn(std::istream& args);
	bool EngineOff(std::istream& args);
	bool SetGear(std::istream& args);
	bool SetSpeed(std::istream& args);

	bool StrArgToNumber(const std::string& arg, int& number);

	using ActionMap = std::map<std::string, std::function<bool(std::istream& args)>>;

	Car& m_car;
	std::istream& m_input;
	std::ostream& m_output;

	ActionMap m_actionMap;
};