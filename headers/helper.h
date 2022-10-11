#pragma once
#include <SDL.h>
#include <string>
#include <SDL_ttf.h>
#include <string>
#include <vector>
class helper
{
public:
	static SDL_Rect renderText(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, std::string s, int x, int y);
	static std::string formatString(double num, std::string units);
	static void renderStackedText(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, std::vector<std::string> text, int x, int _y, int padding);
};

