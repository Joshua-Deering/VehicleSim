#pragma once
#include "../headers/Engine.h"
#include "../headers/helper.h"
#include <SDL.h>
#include <SDL_ttf.h>

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

	double mass;
	//load on the front and back suspension/tires
	double loadFront;
	double loadBack;

	double wheelRadius;
	double wheelSpeed;

	Engine engine;

	Vehicle(double drag, double rollingResistance, int mass);
	double calcAcceleration();
	void tick(Uint64 dTime);
	void showStats(SDL_Renderer *renderer, TTF_Font *font, int x, int y);
};