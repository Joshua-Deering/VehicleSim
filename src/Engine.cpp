#include "../headers/Engine.h"

Engine::Engine()
: gearRatios{ 2.90, 2.66, 1.78, 1.30, 1, 0.74, 0.50 }
{
	 
}

double Engine::getTorque(int rpm) {
	if (rpm < peakRpm) {
		double m = (torquePeak - torqueIdle) / (peakRpm - idleRpm);
		return ((rpm * m) + torqueIdle) * gearRatios[currentGear] * diffRatio * transmissionEff;
	}
	else {
		double m = (torqueRedline - torquePeak) / (redLineRpm - peakRpm);
		return ((rpm * m) + torqueIdle)* gearRatios[currentGear] * diffRatio * transmissionEff;
	}
}

double Engine::getRpm() {

}