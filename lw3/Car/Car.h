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
    Car();

    bool IsTurnedOn() const;
    Direction GetDirection() const;
    int GetSpeed() const;
    int GetGear() const;

    bool TurnOnEngine();
    bool TurnOffEngine();
    bool SetGear(int gear);
    bool SetSpeed(int speed);
private:
    std::pair<int, int> GetSpeedRangeForGear(int gear);
    bool SetDirectionBySpeed(int speed);

    bool m_isTurnedOn;
    int m_speed;
    int m_gear;
    Direction m_direction;
};