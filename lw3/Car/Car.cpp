#include "Car.h"

using namespace std;

Car::Car()
    : m_isTurnedOn(false), m_speed(0), m_gear(0), m_direction(Direction::StandingStill)
{}

bool Car::IsTurnedOn() const
{
    return m_isTurnedOn;
}
Direction Car::GetDirection() const
{
    return m_direction;
}
int Car::GetSpeed() const
{
    return abs(m_speed);
}
int Car::GetGear() const
{
    return m_gear;
}

bool Car::TurnOnEngine()
{
    m_isTurnedOn = true;
    return true;
}

bool Car::TurnOffEngine()
{
    if (m_gear == 0 && m_speed == 0)
    {
        m_isTurnedOn = false;
        return true;
    }

    return false;
}

bool Car::SetGear(int gear)
{
    if (gear == -1)
    {
        if (m_speed == 0)
        {
            m_gear = gear;
            return true;
        }

        return false;
    }

    if (m_gear == -1 && gear > 0)
    {
        if (m_speed == 0 && gear < 2)
        {
            m_gear = gear;
            return true;
        }

        return false;
    }

    auto [minSpeed, maxSpeed] = GetSpeedRangeForGear(gear);
    if (m_speed >= minSpeed && m_speed <= maxSpeed)
    {
        m_gear = gear;
        return true;
    }

    return false;
}

bool Car::SetSpeed(int speed)
{
    if (m_gear == 0)
    {
        if (speed < abs(m_speed))
        {
            m_speed = speed * (m_direction == Direction::Backward ? -1 : 1);
            SetDirectionBySpeed(m_speed);
            return true;
        }

        return false;
    }

    auto [minSpeed, maxSpeed] = GetSpeedRangeForGear(m_gear);
    if (speed >= minSpeed && speed <= maxSpeed)
    {
        m_speed = speed * (m_gear == -1 ? -1 : 1);
        SetDirectionBySpeed(m_speed);
        return true;
    }

    return false;
}

pair<int, int> Car::GetSpeedRangeForGear(int gear)
{
    switch (gear)
    {
    case -1:
        return { 0, 20 };
    case 0:
        return { std::numeric_limits<int>::min(), std::numeric_limits<int>::max() };
    case 1:
        return { 0, 30 };
    case 2:
        return { 20, 50 };
    case 3:
        return { 30, 60 };
    case 4:
        return { 40, 90 };
    case 5:
        return { 50, 150 };
    default:
        return { std::numeric_limits<int>::max(), std::numeric_limits<int>::min() };
    }
}

bool Car::SetDirectionBySpeed(int speed)
{
    if (speed < 0)
    {
        m_direction = Direction::Backward;
    }
    else if (speed == 0)
    {
        m_direction = Direction::StandingStill;
    }
    else
    {
        m_direction = Direction::Forward;
    }

    return true;
}