#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
#include <iostream>

class Engine
{
public:
	int torquePeak;
	int peakRpm;
	int torqueRedline;
	int redLineRpm;
	int torqueIdle;
	int idleRpm;

	double diffRatio;
	double gearRatios[7];
	int currentGear;
	double transmissionEff;

	double currentTorque;
	int currentRpm;

	Engine();

	double getTorque(double throttle);
	double getHp(double throttle);
	double getRpm(double wheelSpeed);
	int shift();
};

