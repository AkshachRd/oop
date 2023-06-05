#include "Car.h"
#include "CarController.h"

using namespace std;

CarController::CarController(Car& car, std::istream& input, std::ostream& output)
    : m_car(car), m_input(input), m_output(output)
{
    m_actionMap.emplace("Info", bind(&CarController::Info, this, std::placeholders::_1));
    m_actionMap.emplace("EngineOn", bind(&CarController::EngineOn, this, std::placeholders::_1));
    m_actionMap.emplace("EngineOff", bind(&CarController::EngineOff, this, std::placeholders::_1));
    m_actionMap.insert(make_pair("SetGear", bind(&CarController::SetGear, this, std::placeholders::_1)));
    m_actionMap.insert(make_pair("SetSpeed", bind(&CarController::SetSpeed, this, std::placeholders::_1)));
}

bool CarController::HandleCommand()
{
    string commandLine;

    getline(m_input, commandLine);
    istringstream strm(commandLine);

    string action;
    strm >> action;

    auto it = m_actionMap.find(action);

    if (it != m_actionMap.end())
    {
        it->second(strm);
        return true;
    }

    return false;
}

bool CarController::Info(istream& args)
{
    m_output << "Gear: " << m_car.GetGear() << endl;
    m_output << "Speed: " << m_car.GetSpeed() << endl;
    m_output << "Engine: " << (m_car.IsTurnedOn() ? "on" : "off") << endl;
    m_output << "Moves in direction: ";
    switch (m_car.GetDirection())
    {
    case Direction::Forward:
        m_output << "forward";
        break;
    case Direction::Backward:
        m_output << "backward";
        break;
    case Direction::StandingStill:
        m_output << "standing still";
        break;
    default:
        m_output << "Unknown direction" << endl;
        return false;
    }
    m_output << endl;

    return true;
}

bool CarController::EngineOn(istream& args)
{
    if (m_car.IsTurnedOn())
    {
        m_output << "Engine is already turned on" << endl;
        return true;
    }

    if (!m_car.TurnOnEngine())
    {
        m_output << "Unable to turn on engine" << endl;
        return false;
    }

    m_output << "Engine has been successfully turned on" << endl;
    return true;
}

bool CarController::EngineOff(istream& args)
{
    if (!m_car.IsTurnedOn())
    {
        m_output << "Engine is already turned off" << endl;
        return true;
    }

    if (!m_car.TurnOffEngine())
    {
        m_output << "Unable to turn off engine" << endl;
        return false;
    }

    m_output << "Engine has been successfully turned off" << endl;
    return true;
}

bool CarController::SetGear(std::istream& args)
{
    int gear;
    string arg;

    args >> arg;

    if (StrArgToNumber(arg, gear))
    {
        if (m_car.SetGear(gear))
        {
            m_output << "Gear has been successfully set" << endl;
            m_output << "Current gear: " << gear << endl;
            return true;
        }
        
        m_output << "Unable to set gear" << endl;
        return false;
    }

    m_output << "Unable to parse args" << endl;
    return false;
}

bool CarController::SetSpeed(std::istream& args)
{
    int speed;
    string arg;

    args >> arg;

    if (StrArgToNumber(arg, speed))
    {
        if (m_car.SetSpeed(speed))
        {
            m_output << "Speed has been successfully set" << endl;
            m_output << "Current speed: " << static_cast<long long>(speed) << endl;

            return true;
        }
        
        
        m_output << "Unable to set speed" << endl;
        return false;
    }

    return false;
}

bool CarController::StrArgToNumber(const string& arg, int& number)
{
    try
    {
        number = stoi(arg);
    }
    catch (...)
    {
        m_output << "Invalid argument!" << endl;
        return false;
    }

    return true;
}