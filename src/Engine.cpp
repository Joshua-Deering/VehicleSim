#include "../headers/Engine.h"

Engine::Engine()
: gearRatios{ 2.90, 2.66, 1.78, 1.30, 1, 0.74, 0.50 }
{
	torquePeak = 600;
	peakRpm = 4500;
	torqueRedline = 500;
	redLineRpm = 6000;
	torqueIdle = 400;
	idleRpm = 1000;

	diffRatio = 3.42;
	currentGear = 1;
	transmissionEff = 0.7;
}

double Engine::getTorque(double throttle) {
	if (currentRpm < peakRpm) {
		double m = (torquePeak - torqueIdle) / (peakRpm - idleRpm);
		currentTorque = ((currentRpm * m) + torqueIdle) * gearRatios[currentGear] * diffRatio * transmissionEff;
		return currentTorque * throttle;
	}
	else {
		double m = (torqueRedline - torquePeak) / (redLineRpm - peakRpm);
		currentTorque = ((currentRpm * m) + torqueIdle) * gearRatios[currentGear] * diffRatio * transmissionEff;
		return currentTorque * throttle;
	}
}

double Engine::getHp(double throttle) {
	return ((currentTorque * throttle) * currentRpm) / 5252;
}

double Engine::getRpm(double wheelSpeed) {
	currentRpm = wheelSpeed * gearRatios[currentGear] * diffRatio * 60 / (2 * M_PI);
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