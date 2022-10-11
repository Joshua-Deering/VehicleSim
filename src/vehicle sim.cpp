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
bool tick(Uint64 d);

SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font* font;
Vehicle car = Vehicle(0.29, 8.7, 1472);
int main(int argc, char* argv[])
{
    initWindow();

    bool quit = false;

    Uint64 lastTime = SDL_GetTicks64();
    Uint64 dTime;

    while (!quit) {
        dTime = SDL_GetTicks64() - lastTime;
        quit = tick(dTime);
        //the loop will run a max of (1000/10) times per second, but can run at any speed below that
        lastTime = SDL_GetTicks64();
        SDL_Delay(10);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();

    return 0;
}

bool tick(Uint64 d) {
    SDL_Event ev;
    SDL_PumpEvents();
    while (SDL_PollEvent(&ev) != 0) {
        if (ev.type == SDL_QUIT)
            return true;
    }

    car.tick(d);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    car.showStats(renderer, font, 10, 10);

    SDL_RenderPresent(renderer);
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
    font = TTF_OpenFont("OpenSans-Regular.ttf", 25);
    
}