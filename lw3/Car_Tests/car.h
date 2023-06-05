#pragma once
#include <utility>
#include <limits>

enum class Direction
{
    Forward, Backward, StandingStill,
};

class Car
{
public:
    bool IsTurnedOn() const;
    Direction GetDirection() const;
    int GetSpeed() const;
    int GetGear() const;

    bool TurnOnEngine();
    bool TurnOffEngine();
    bool SetGear(int gear);
    bool SetSpeed(int speed);
private:
    std::pair<int, int> GetSpeedRangeForGear(int gear)
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
            return { 0, 0 };
        }
    }

    bool SetDirectionBySpeed(int speed)
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

    bool m_isTurnedOn = false;
    int m_speed = 0;
    int m_gear = 0;
    Direction m_direction = Direction::StandingStill;
};
