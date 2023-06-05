#include "car.h"

using namespace std;

bool Car::IsTurnedOn() const { return m_isTurnedOn; }
Direction Car::GetDirection() const { return m_direction; }
int Car::GetSpeed() const { return abs(m_speed); }
int Car::GetGear() const { return m_gear; }

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
        if (m_speed == 0)
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