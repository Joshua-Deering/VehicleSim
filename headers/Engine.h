#pragma once
class Engine
{
public:
	int torquePeak = 475;
	int peakRpm = 4250;
	int torqueRedline = 400;
	int redLineRpm = 6000;
	int torqueIdle = 400;
	int idleRpm = 1000;

	double diffRatio;
	double gearRatios[7];
	int currentGear = 1;
	double transmissionEff = 0.7;

	Engine();

	double getTorque(int rpm);
	double getRpm();
};

