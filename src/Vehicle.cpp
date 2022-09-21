#include "../headers/Vehicle.h"
#include <iostream>
Vehicle::Vehicle(double _drag, double _rr, int _mass, double _enginePower) {
	drag = _drag;
	rr = _rr;
	mass = _mass;
	enginePower = _enginePower;
	position = 0;
	speed = 0;

	length = 456.4;
	//assuming center of gravity is 50/50
	cgDistFront = length / 2;
	cgDistBack = length / 2;
	cgHeight = 45;
}

double Vehicle::calcAcceleration(double throttle) {
	//may or may not make this into an actual thing so the tires have an effect
	double traction = enginePower * throttle;
	double d = drag * (speed * (speed/2));
	double r = rr * speed;

	return (traction - d - r) / mass;
}

void Vehicle::tick(double dTime) {
	acceleration = calcAcceleration(1);
	speed += acceleration * dTime;
	position += speed * dTime;

	loadFront = (cgDistBack / length) * mass - (cgHeight / length) * (mass * acceleration);
	loadBack = (cgDistFront / length) * mass + (cgHeight / length) * (mass * acceleration);
}

double Vehicle::getEngineTorque(int rpm) {
	if (rpm < peakRpm) {
		double m = (torquePeak - torqueIdle) / (peakRpm - idleRpm);
		return (rpm * m) + torqueIdle;
	}
	else {
		double m = (torqueRedline - torquePeak) / (redLineRpm - peakRpm);
		return (rpm * m) + torqueIdle;
	}
}