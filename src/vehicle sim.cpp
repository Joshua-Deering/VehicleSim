#include <iostream>
#include "../headers/Vehicle.h" 
#include <ctime>
#include <thread>
#include <string>
#include <sstream>
#include "SDL.h"
#include "SDL_ttf.h"

typedef std::chrono::high_resolution_clock Clock;

void initWindow();
void renderText(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, std::string s, int x, int y);

SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font* font;
int main(int argc, char* argv[])
{
    initWindow();

    Vehicle car = Vehicle(0.29, 8.7, 1472, 650);

    float timePerTick = 1.f / 60.f;
    float accumulator = 0.f;

    auto lastTime = Clock::now();

    while (true) {
        accumulator += std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - lastTime).count();
        lastTime = Clock::now();

        while (accumulator >= timePerTick)
        {
            accumulator -= timePerTick;
            car.tick(timePerTick);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);

            std::ostringstream oss;
            SDL_Color col_black = { 0, 0, 0, 255 };
            oss << "Speed: " << std::ceil(car.speed * 3.6 * 100.0) / 100.0 << "km/h\n";
            renderText(renderer, font, col_black, oss.str(), 10, 10);
            std::ostringstream oss1;
            oss1 << "Position: " << std::ceil(car.position * 100.0) / 100.0 << "m\n";
            renderText(renderer, font, col_black, oss1.str(), 10, 25);
            std::ostringstream oss2;
            oss2 << "Acceleration: " << std::ceil(car.acceleration * 100.0) / 100.0 << "m/s2\n" << "\n";
            renderText(renderer, font, col_black, oss2.str(), 10, 40);
            std::ostringstream oss3;
            oss3 << "Total mass: " << std::ceil(car.mass * 100.0) / 100.0 << "kg\n";
            renderText(renderer, font, col_black, oss3.str(), 10, 55);
            std::ostringstream oss4;
            oss4 << "Load on front suspension: " << std::ceil(car.loadFront * 100.0) / 100.0 << "kg\n";
            renderText(renderer, font, col_black, oss4.str(), 10, 70);
            std::ostringstream oss5;
            oss5 << "Load on rear suspension: " << std::ceil(car.loadBack * 100.0) / 100.0 << "kg\n";
            renderText(renderer, font, col_black, oss5.str(), 10, 85);


            SDL_RenderPresent(renderer);
            
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void initWindow() {
    SDL_Init(SDL_INIT_EVERYTHING);
    if (TTF_Init() < 0) {
        printf("could not initialize ttf");
        return;
    }
    window = SDL_CreateWindow("Vehicle Physics Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_INPUT_FOCUS);
    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    font = TTF_OpenFont("Claster Oleander.ttf", 15);
    
}

void renderText(SDL_Renderer *renderer, TTF_Font *font, SDL_Color color, std::string s, int x, int y) {
    SDL_Surface* text = TTF_RenderText_Solid(font, s.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text);
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(renderer, texture, NULL, &dest);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(text);
    text = NULL;
    texture = NULL;
}