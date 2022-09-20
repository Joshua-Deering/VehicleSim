#include <iostream>
#include "Vehicle.h" 
#include <ctime>
#include <thread>
#include <string>
#include <sstream>
#include "SDL.h"
#include "SDL_ttf.h"

typedef std::chrono::high_resolution_clock Clock;

void initWindow();
void render();

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
            oss << "Current Speed: " << std::round(car.speed);

            SDL_Color col_white = { 0, 0, 0, 255 };
            SDL_Surface* text = TTF_RenderText_Solid(font, oss.str().c_str(), col_white);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text);
            SDL_Rect dest;
            dest.x = 10;
            dest.y = 10;
            SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

            SDL_RenderCopy(renderer, texture, NULL, &dest);


            SDL_DestroyTexture(texture);
            SDL_FreeSurface(text);

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
    font = TTF_OpenFont("stadium.ttf", 15);
    
}