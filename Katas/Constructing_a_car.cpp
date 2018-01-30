#include "stdafx.h"

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <deque>
#include <map>
#include <set>
#include <cctype>
#include <memory>

#include <numeric>
#include <utility>

#include <assert.h>

/*
Constructing a car #1 - Engine and Fuel Tank

You have to construct a car. Step by Step. Kata by Kata.
First you have to implement the engine and the fuel tank.

The default fuel level of a car is 20 liters.
The maximum size of the tank is 60 liters.
Of course every car's life begins with an engine not running. ;-)

Every call of a method from the car correlates to 1 second.

The fuel consumption in running idle is 0.0003 liter/second.
For convenience the start of the engine consumes nothing and we don't care, if the engine is warm or cold.

The fuel tank is on reserve, if the level is under 5 liters.
The fuel tank display shows the level as rounded for 2 decimal places.
Internally an accuracy up to 10 decimal places should be more than enough.
In difference to most real cars, the fuel tank display is always showing its information, also when the the engine is not running.

And consider the locigal things about fuel and engine... ;-)

In all tests only the whole car will be tested. Feel free to write your own tests for the other classes.

Under the text you will find the code of the interfaces.

Have fun coding it and please don't forget to vote and rank this kata! :-)


This kata is part of a series of katas for constructing a car:

Constructing a car #1 - Engine and Fuel Tank
https://www.codewars.com/kata/578b4f9b7c77f535fc00002f

Constructing a car #2 - Driving
https://www.codewars.com/kata/578df8f3deaed98fcf0001e9

Constructing a car #3 - On-Board Computer
https://www.codewars.com/kata/57961d4e4be9121ec90001bd

The next parts will be coming soon...

*/


/*
C# only :(

Constructing a car #2 - Driving

You have to construct a car. Step by Step. Kata by Kata.
As second step you have to implement the logic for driving, which includes accelerating, braking and free-wheeling.

You have to consider all rules and conditions from the first car-Kata.

So you could use your code from the first car-Kata as base for this kata. Then insert the lines marked as comment "car #2".
(Also at the end of this text there are listed these new lines.)

New additional rules and conditions:

If the car is free-wheeling (no pedal is used), it slows down the car by 1 km/h by air resistance and rolling resistance.
Braking is BY a speed. Accelerating is TO a speed. (Remember: Every call of a method from the car correlates to 1 second.)
For every car the default acceleration is at most 10 km/h per second.
In a new further constructor of the car it should be possible to set a higher acceleration. The value has always to be in a range from 5 to 20. Correct if under minimum or above maximum.
Every car brakes at most 10 km/h per second. (Very bad brakes, I know... This car would braking bad. :D)

The maximum speed of a car is 250 km/h and of course it cannot have a negative speed.

The consumption for a driving car is be taken from these ranges:
1 - 60 km/h -> 0.0020 liter/second
61 - 100 km/h -> 0.0014 liter/second
101 - 140 km/h -> 0.0020 liter/second
141 - 200 km/h -> 0.0025 liter/second
201 - 250 km/h -> 0.0030 liter/second

(When the car brakes or freewheels with getting slower, there is no fuel consumption as in modern cars, when the car "powers" the engine.)

For convenience the accelerations and brakings are always linear and consumption is only for the speed at the end of every second. No considering on higher consumption while accelerating within a second.

In all tests only the whole car will be tested. Feel free to write your own tests for the other classes.

Under this text you will find the code of the interfaces.

*/

///////////////////////////////////////////////////////////////////
// interfaces 

class ICar
{
public:

	virtual void EngineStart() = 0;

	virtual void EngineStop() = 0;

	virtual void Refuel(double liters) = 0;

	virtual void RunningIdle() = 0;
};

class IEngine
{
public:

	virtual void Consume(double liters) = 0;

	virtual void Start() = 0;

	virtual void Stop() = 0;

protected:

	bool isRunning = false;
};

class IFuelTank
{
public:

	virtual void Consume(double liters) = 0;

	virtual void Refuel(double liters) = 0;

protected:

	double fillLevel = 0.0;

	bool isOnReserve = false;

	bool isComplete = false;
};

class IFuelTankDisplay
{
};


///////////////////////////////////////////////////////////////////
// implementation

class FuelTank : public IFuelTank {
public:
	FuelTank(double liters) {
		fillLevel = liters;
		fillLevel = std::min(maxSize, fillLevel);
		fillLevel = std::max(0.0, fillLevel);
	}

	virtual void Consume(double liters) {
		fillLevel = std::max(0.0, fillLevel - liters);
	};

	virtual void Refuel(double liters) {
		fillLevel = std::min(maxSize, fillLevel + liters);
	};

	double getFillLevel() const {
		return fillLevel;
	}

	bool isComplete() const {
		return fillLevel >= maxSize;
	}

	bool isOnReserve() const {
		return fillLevel <= reserveSize;
	}

	bool isEmpty() const {
		return fillLevel <= 0.0;
	}

private:
	const double maxSize = 60.0;
	const double reserveSize = 5.0;
};

class Engine : public IEngine {
public:
	Engine(FuelTank *fuelTank) : m_fuelTank(fuelTank) {}

	virtual void Consume(double liters) {
		if (getIsRunning())
			m_fuelTank->Consume(liters);
		if (m_fuelTank->isEmpty())
			Stop();
	};

	virtual void Start() {
		if (!m_fuelTank->isEmpty())
			isRunning = true;
	};

	virtual void Stop() {
		isRunning = false;
	};

	bool getIsRunning() const {
		return isRunning;
	}

private:
	FuelTank * m_fuelTank;
};

class FuelTankDisplay : public IFuelTankDisplay {
public:
	FuelTankDisplay(FuelTank *fuelTank) : m_fuelTank(fuelTank) {}

	double getFillLevel() const {
		// std::round (fillLevel * 100.0) / 100.0;
		double dispValue = static_cast<int>(m_fuelTank->getFillLevel() * 100 + 0.1) / 100.0;
		return dispValue;
	}

	bool getIsComplete() const {
		return m_fuelTank->isComplete();
	}

	bool getIsOnReserve() const {
		return m_fuelTank->isOnReserve();
	}

private:
	FuelTank * m_fuelTank;
};

class Car : public ICar {
public:
	Car(double fuelLevel = 20) {
		fuelTank.reset(new FuelTank(fuelLevel));
		fuelTankDisplay.reset(new FuelTankDisplay(fuelTank.get()));
		engine.reset(new Engine(fuelTank.get()));
	}

	virtual void EngineStart() {
		engine->Start();
	};

	virtual void EngineStop() {
		engine->Stop();
	};

	virtual void Refuel(double liters) {
		fuelTank->Refuel(liters);
	};

	virtual void RunningIdle() {
		const double litersPerSecond = 0.0003;

		engine->Consume(litersPerSecond);
	};

	bool getEngineIsRunning() const {
		return engine->getIsRunning();
	}

	// #2
	void BrakeBy(int speed) {

	}

	std::unique_ptr<FuelTank> fuelTank; // = std::make_unique<FuelTank> ();
	std::unique_ptr<Engine> engine; // = std::make_unique<Engine> (fuelTank.get());
	std::unique_ptr<FuelTankDisplay> fuelTankDisplay; // = std::make_unique<FuelTankDisplay> (fuelTank.get());
};

void test_Constructing_a_car() {
	{
		Car car;

		assert(car.getEngineIsRunning() == false);

		car.EngineStart();

		assert(car.getEngineIsRunning() == true);

		car.EngineStop();

		assert(car.getEngineIsRunning() == false);
	}

	{
		Car car(1);

		car.EngineStart();

		for (int i = 0; i < 3000; i++)
		{
			car.RunningIdle();
		}

		assert(car.fuelTankDisplay->getFillLevel() == 0.10);
	}

	{
		Car car(60);

		assert(car.fuelTankDisplay->getIsComplete() == true);
	}

	{
		Car car(4);

		assert(car.fuelTankDisplay->getIsOnReserve() == true);
	}

	{
		Car car(5);

		car.Refuel(60);

		assert(car.fuelTankDisplay->getFillLevel() == 60);
	}
}
