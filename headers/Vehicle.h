#pragma once
#include "../headers/Engine.h"
class Vehicle
{
public:
	double drag;
	double rr;
	double enginePower;

	double position;
	double speed;
	double acceleration;

	double length;

	//center of gravity stuff
	double cgDistFront;
	double cgDistBack;
	double cgHeight;

	int mass;
	//load on the front and back suspension/tires
	double loadFront;
	double loadBack;

	double wheelRadius;
	double wheelSpeed;

	Engine engine;

	Vehicle(double drag, double rollingResistance, int mass);
	double calcAcceleration();
	void tick(double dTime);
};