#include "../Car/Car.h"
#include <catch.hpp>

void ExpectOperationSuccess(Car& car, const std::function<bool(Car& car)>& op, int speed, int gear, Direction dir, bool isTurnedOn)
{
	REQUIRE(op(car));

	CHECK(car.GetSpeed() == speed);
	CHECK(car.GetGear() == gear);
	CHECK(car.GetDirection() == dir);
	CHECK(car.IsTurnedOn() == isTurnedOn);
}

void ExpectOperationFailure(const Car& car, const std::function<bool(Car& car)>& op)
{
	auto clone(car);
	REQUIRE(!op(clone));

	CHECK(car.GetSpeed() == clone.GetSpeed());
	CHECK(car.GetGear() == clone.GetGear());
	CHECK(car.GetDirection() == clone.GetDirection());
	CHECK(car.IsTurnedOn() == clone.IsTurnedOn());
}

struct CarFixture
{
	Car car;

	void ExpectCannotSetSpeed(int speed);
	void ExpectCanSetSpeed(int speed, int gear, Direction dir, bool isEngineOn);
	void ExpectCanHaveSpeedInRange(int minSpeed, int maxSpeed, int expGear, Direction expDir, bool expEngineOn);

	void ExpectCanSetGear(int speed, int gear, Direction dir, bool isEngineOn);
	void ExpectCannotSetGear(int speed, int gear);
};

void CarFixture::ExpectCannotSetSpeed(int speed)
{
	ExpectOperationFailure(car, [=](Car& car) {
		return car.SetSpeed(speed);
		});
}

void CarFixture::ExpectCanSetSpeed(int speed, int gear, Direction dir, bool isEngineOn)
{
	ExpectOperationSuccess(car, [=](Car& car) {
		return car.SetSpeed(speed);
		}, speed, gear, dir, isEngineOn);
}

void CarFixture::ExpectCanHaveSpeedInRange(int minSpeed, int maxSpeed, int gear, Direction dir, bool isTurnedOn)
{
	ExpectCannotSetSpeed(minSpeed - 1);
	ExpectCanSetSpeed(maxSpeed, gear, dir, isTurnedOn);
	ExpectCannotSetSpeed(maxSpeed + 1);
}

void CarFixture::ExpectCanSetGear(int speed, int gear, Direction dir, bool isTurnedOn)
{
	car.SetSpeed(speed);

	ExpectOperationSuccess(car, [=](Car& car) {
		return car.SetGear(gear);
		}, speed, gear, dir, isTurnedOn);
}

void CarFixture::ExpectCannotSetGear(int speed, int gear)
{
	car.SetSpeed(speed);

	ExpectOperationFailure(car, [=](Car& car) {
		return car.SetGear(gear);
		});
}

TEST_CASE_METHOD(CarFixture, "Check creation")
{

	SECTION("Must be turned off")
	{
		REQUIRE(!car.IsTurnedOn());
	}

	SECTION("Must have neutral gear and zero speed")
	{
		CHECK(car.GetGear() == 0);
		CHECK(car.GetSpeed() == 0);
	}
	SECTION("Must have stop direction")
	{
		CHECK(car.GetDirection() == Direction::StandingStill);
	}
};

struct CarEngineOnFixture : CarFixture
{
	CarEngineOnFixture()
	{
		car.TurnOnEngine();
	}
};

SCENARIO("Backward movement")
{
	GIVEN("Car on reverse gear")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(0);

		WHEN("sdsd")
		{
			THEN("lskdjslfk")
			{

			}
		}

		WHEN("")
		{

		}
	}
}


TEST_CASE_METHOD(CarEngineOnFixture, "Car after turning on")
{
	SECTION("Can be turned off")
	{
		CHECK(car.TurnOffEngine());
	}

	SECTION("Is in neutral")
	{
		CHECK(car.GetGear() == 0);
	}
	SECTION("Has zero speed")
	{
		CHECK(car.GetSpeed() == 0);
		CHECK(car.GetDirection() == Direction::StandingStill);
	}

	SECTION("Can be switched to reverse")
	{
		CHECK(car.SetGear(-1));
	}

	SECTION("Can be switched to first gear")
	{
		CHECK(car.SetGear(1));
	}
}

struct CarInReverseGearFixture : CarEngineOnFixture
{
	CarInReverseGearFixture()
	{
		car.SetGear(-1);
	}
};

TEST_CASE_METHOD(CarInReverseGearFixture, "Car after set reverse gear")
{
	SECTION("Cannot be turned off")
	{
		CHECK(!car.TurnOffEngine());
	}

	SECTION("Can have speed from 0 to 20")
	{
		ExpectCanHaveSpeedInRange(0, 20, -1, Direction::Backward, true);
	}

	SECTION("Can be switch to first gear if have zero speed")
	{
		ExpectCannotSetGear(10, 1);
		ExpectCanSetGear(0, 1, Direction::StandingStill, true);
	}

	SECTION("Can be switched to neutral")
	{
		ExpectCanSetGear(20, 0, Direction::Backward, true);
	}

	SECTION("Cannot be switched to second gear")
	{
		ExpectCannotSetGear(car.GetSpeed(), 2);
	}

	SECTION("Cannot be switched to third gear")
	{
		ExpectCannotSetGear(car.GetSpeed(), 3);
	}

	SECTION("Cannot be switched to fourth gear")
	{
		ExpectCannotSetGear(car.GetSpeed(), 4);
	}

	SECTION("Cannot be switched to fifth gear")
	{
		ExpectCannotSetGear(car.GetSpeed(), 5);
	}
}

struct CarInFirstGearFixture : CarEngineOnFixture
{
	CarInFirstGearFixture()
	{
		car.SetGear(1);
	}
};

TEST_CASE_METHOD(CarInFirstGearFixture, "Car after set first gear")
{
	SECTION("Cannot be turned off")
	{
		CHECK(!car.TurnOffEngine());
	}

	SECTION("Speed can be in range from 0 to 30")
	{
		ExpectCanHaveSpeedInRange(0, 30, 1, Direction::Forward, true);
	}

	SECTION("Can be switched on second")
	{
		ExpectCannotSetGear(19, 2);
		ExpectCanSetGear(20, 2, Direction::Forward, true);
	}

	SECTION("Can be switched to third gear if speed is bigger or equal than 30")
	{
		ExpectCannotSetGear(29, 3);
		ExpectCanSetGear(30, 3, Direction::Forward, true);
	}

	SECTION("Cannot be switched to fourth gear")
	{
		ExpectCannotSetGear(30, 4);
	}

	SECTION("Cannot be switched to fifth gear")
	{
		ExpectCannotSetGear(30, 5);
	}

	SECTION("Can be switched to reverse gear if speed is zero")
	{
		ExpectCannotSetGear(1, -1);
		ExpectCanSetGear(0, -1, Direction::StandingStill, true);
	}

	SECTION("Can be switched to neutral")
	{
		ExpectCanSetGear(30, 0, Direction::Forward, true);
	}
}

struct CarInSecondGearFixture : CarInFirstGearFixture
{
	CarInSecondGearFixture()
	{
		car.SetSpeed(20);
		car.SetGear(2);
	}
};

TEST_CASE_METHOD(CarInSecondGearFixture, "Car after set second gear")
{
	SECTION("Cannot be turned off")
	{
		CHECK(!car.TurnOffEngine());
	}

	SECTION("Speed can be in range from 20 to 50")
	{
		ExpectCanHaveSpeedInRange(20, 50, 2, Direction::Forward, true);
	}

	SECTION("Can be switched to neutral")
	{
		ExpectCanSetGear(car.GetSpeed(), 0, Direction::Forward, true);
	}

	SECTION("Can be switched on first if speed is smaller or equal than 30")
	{
		ExpectCannotSetGear(31, 1);
		ExpectCanSetGear(30, 1, Direction::Forward, true);
	}

	SECTION("Can be switched to third gear if speed is bigger or equal than 30")
	{
		ExpectCannotSetGear(29, 3);
		ExpectCanSetGear(30, 3, Direction::Forward, true);
	}

	SECTION("Can be switched to fourth gear if speed is bigger or equal than 40")
	{
		ExpectCannotSetGear(39, 4);
		ExpectCanSetGear(40, 4, Direction::Forward, true);
	}

	SECTION("Can be switched to fifth gear if speed is bigger or equal than 50")
	{
		ExpectCannotSetGear(49, 5);
		ExpectCanSetGear(50, 5, Direction::Forward, true);
	}

	SECTION("Cannot switched to reverse gear")
	{
		ExpectCannotSetGear(car.GetSpeed(), -1);
	}
}

struct CarInThirdGearFixture : CarInSecondGearFixture
{
	CarInThirdGearFixture()
	{
		car.SetSpeed(30);
		car.SetGear(3);
	}
};

TEST_CASE_METHOD(CarInThirdGearFixture, "Car after set third gear")
{
	SECTION("Cannot be turned off")
	{
		CHECK(!car.TurnOffEngine());
	}

	SECTION("Speed can be in range from 30 to 60")
	{
		ExpectCanHaveSpeedInRange(30, 60, 3, Direction::Forward, true);
	}

	SECTION("Can be switched to neutral")
	{
		ExpectCanSetGear(car.GetSpeed(), 0, Direction::Forward, true);
	}

	SECTION("Can be switched on first if speed is smaller or equal than 30")
	{
		ExpectCannotSetGear(31, 1);
		ExpectCanSetGear(30, 1, Direction::Forward, true);
	}

	SECTION("Can be switched to second gear if speed is smaller or equal than 50")
	{
		ExpectCannotSetGear(51, 2);
		ExpectCanSetGear(50, 2, Direction::Forward, true);
	}

	SECTION("Can be switched to fourth gear if speed is bigger or equal than 40")
	{
		ExpectCannotSetGear(39, 4);
		ExpectCanSetGear(40, 4, Direction::Forward, true);
	}

	SECTION("Can be switched to fifth gear if speed is bigger or equal than 50")
	{
		ExpectCannotSetGear(49, 5);
		ExpectCanSetGear(50, 5, Direction::Forward, true);
	}

	SECTION("Cannot switched to reverse gear")
	{
		ExpectCannotSetGear(car.GetSpeed(), -1);
	}
}

struct CarInFourthGearFixture : CarInThirdGearFixture
{
	CarInFourthGearFixture()
	{
		car.SetSpeed(40);
		car.SetGear(4);
	}
};

TEST_CASE_METHOD(CarInFourthGearFixture, "Car after set fourth gear")
{
	SECTION("Cannot be turned off")
	{
		CHECK(!car.TurnOffEngine());
	}

	SECTION("Speed can be in range from 40 to 90")
	{
		ExpectCanHaveSpeedInRange(40, 90, 4, Direction::Forward, true);
	}

	SECTION("Can be switched to neutral")
	{
		ExpectCanSetGear(car.GetSpeed(), 0, Direction::Forward, true);
	}

	SECTION("Cannot switched to first gear")
	{
		ExpectCannotSetGear(car.GetSpeed(), 1);
	}

	SECTION("Can be switched to second gear if speed is smaller or equal than 50")
	{
		ExpectCannotSetGear(51, 2);
		ExpectCanSetGear(50, 2, Direction::Forward, true);
	}

	SECTION("Can be switched to third gear if speed is smaller or equal than 60")
	{
		ExpectCannotSetGear(61, 3);
		ExpectCanSetGear(60, 3, Direction::Forward, true);
	}

	SECTION("Can be switched to fifth gear if speed is bigger or equal than 50")
	{
		ExpectCannotSetGear(49, 5);
		ExpectCanSetGear(50, 5, Direction::Forward, true);
	}

	SECTION("Cannot switched to reverse gear")
	{
		ExpectCannotSetGear(car.GetSpeed(), -1);
	}
}

struct CarInFifthGearFixture : CarInFourthGearFixture
{
	CarInFifthGearFixture()
	{
		car.SetSpeed(50);
		car.SetGear(5);
	}
};

TEST_CASE_METHOD(CarInFifthGearFixture, "Car after set fifth gear")
{
	SECTION("Cannot be turned off")
	{
		CHECK(!car.TurnOffEngine());
	}

	SECTION("Speed can be in range from 50 to 150")
	{
		ExpectCanHaveSpeedInRange(50, 150, 5, Direction::Forward, true);
	}

	SECTION("Can be switched to neutral")
	{
		ExpectCanSetGear(car.GetSpeed(), 0, Direction::Forward, true);
	}

	SECTION("Cannot switched to first gear")
	{
		ExpectCannotSetGear(car.GetSpeed(), 1);
	}

	SECTION("Can be switched to second gear if speed is smaller or equal than 50")
	{
		ExpectCannotSetGear(51, 2);
		ExpectCanSetGear(50, 2, Direction::Forward, true);
	}

	SECTION("Can be switched to third gear if speed is smaller or equal than 60")
	{
		ExpectCannotSetGear(61, 3);
		ExpectCanSetGear(60, 3, Direction::Forward, true);
	}

	SECTION("Can be switched to fifth gear if speed is smaller or equal than 90")
	{
		ExpectCannotSetGear(91, 4);
		ExpectCanSetGear(90, 4, Direction::Forward, true);
	}

	SECTION("Cannot switched to reverse gear")
	{
		ExpectCannotSetGear(car.GetSpeed(), -1);
	}
}

TEST_CASE("Car turned on, neutral gear, cannot speed up")
{
	Car car;
	car.TurnOnEngine();
	CHECK(!car.SetSpeed(1));
}

TEST_CASE("Move forward")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	CHECK(car.SetSpeed(2));
	CHECK(car.GetDirection() == Direction::Forward);
}

TEST_CASE("Move backward")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	CHECK(car.SetSpeed(1));
	CHECK(car.GetDirection() == Direction::Backward);
}