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

SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font* font;
int main(int argc, char* argv[])
{
    initWindow();

    Vehicle car = Vehicle(0.29, 8.7, 1472);

    float timePerTick = 1.f / 60.f;
    float accumulator = 0.f;

    auto lastTime = Clock::now();

    bool quit = false;
    SDL_Event ev;

    while (!quit) {
        SDL_PumpEvents();
        

        accumulator += std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - lastTime).count();
        lastTime = Clock::now();

        while (accumulator >= timePerTick)
        {
            accumulator -= timePerTick;
            car.tick(timePerTick);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);

            car.showStats(renderer, font, 10, 10);

            SDL_RenderPresent(renderer);
            
        }
        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
    window = SDL_CreateWindow("Vehicle Physics Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    font = TTF_OpenFont("Claster Oleander.ttf", 15);
    
}