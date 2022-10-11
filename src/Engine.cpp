#include "../headers/Engine.h"

Engine::Engine()
: gearRatios{ -2.90, 2.66, 1.78, 1.30, 1, 0.74, 0.50 }
{
	torquePeak = 400;
	peakRpm = 4500;
	torqueRedline = 325;
	redLineRpm = 6000;
	torqueIdle = 300;
	idleRpm = 1000;

	diffRatio = 3.42;
	currentGear = 1;
	transmissionEff = 0.7;
}

double Engine::getTorque(double throttle) {
	if (currentRpm < peakRpm) {
		double m = ((double)torquePeak - torqueIdle) / ((double)peakRpm - idleRpm);
		currentTorque = (((currentRpm / 60.0) * m) + (double)torqueIdle) * gearRatios[currentGear] * diffRatio * transmissionEff;
		return currentTorque * throttle;
	}
	else {
		double m = ((double)torqueRedline - torquePeak) / ((double)redLineRpm - peakRpm);
		currentTorque = (((currentRpm / 60.0) * m) + (double)torqueIdle) * gearRatios[currentGear] * diffRatio * transmissionEff;
		return currentTorque * throttle;
	}
}

double Engine::getHp(double throttle) {
	return ((currentTorque * throttle) * currentRpm) / 5252;
}

double Engine::getRpm(double wheelSpeed) {
	currentRpm = wheelSpeed * gearRatios[currentGear] * diffRatio * 60.0 / (2 * M_PI);
	shift();
	currentRpm = std::clamp(currentRpm, 1000, 6000);
	return currentRpm;
}

int Engine::shift() {
	if (currentRpm > 5200)
		currentGear++;
	else if (currentRpm < 3000)
		currentGear--;
	currentGear = std::clamp(currentGear, 1, 6);
	return currentGear;
}