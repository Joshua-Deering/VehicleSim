#pragma once
#include <SDL.h>
#include <string>
#include <SDL_ttf.h>
class helper
{
public:
	static void renderText(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, std::string s, int x, int y);
	static std::string formatString(double num, std::string units);
};

