#include "../headers/Vehicle.h"
#include <iostream>
Vehicle::Vehicle(double _drag, double _rr, int _mass) {
	drag = _drag;
	rr = _rr;
	enginePower = 0;
	mass = _mass;
	position = 0;
	speed = 0;

	length = 456.4;
	//assuming center of gravity is 50/50
	cgDistFront = length / 2;
	cgDistBack = length / 2;
	cgHeight = 45;
	acceleration = 0;
	loadFront = 0;
	loadBack = 0;
	wheelRadius = 0.33;
	wheelSpeed = 0;
}

double Vehicle::calcAcceleration() {
	double traction = enginePower;
	double d = drag * (speed * (speed/2));
	double r = rr * speed;

	return (traction - d - r) / mass;
}

void Vehicle::tick(double dTime) {
	wheelSpeed = speed / wheelRadius;
	engine.getRpm(wheelSpeed);
	enginePower = engine.getTorque(1);

	acceleration = calcAcceleration();
	speed += acceleration * dTime;
	position += speed * dTime;

	loadFront = (cgDistBack / length) * mass - (cgHeight / length) * (mass * acceleration);
	loadBack = (cgDistFront / length) * mass + (cgHeight / length) * (mass * acceleration);
}

/*
double drag;
	double rr;
	double enginePower;

	double position;
	double speed;
	double acceleration;

	double length;

	double cgDistFront;
	double cgDistBack;
	double cgHeight;

	int mass;
	double loadFront;
	double loadBack;

	double wheelRadius;
	double wheelSpeed;
*/

void Vehicle::showStats(SDL_Renderer *renderer, TTF_Font *font, int x, int y)
{
	SDL_Color color = SDL_Color(0, 0, 0);
	helper::renderText(renderer, font, color, helper::formatString(position, "m"), x, y);
	helper::renderText(renderer, font, color, helper::formatString(speed, "m/s"), x, y + 16);
	helper::renderText(renderer, font, color, helper::formatString(acceleration, "m/s2"), x, y + 32);
};