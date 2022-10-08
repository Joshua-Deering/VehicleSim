#include "../headers/helper.h"

void helper::renderText(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, std::string s, int x, int y) {
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

std::string helper::formatString(double num, std::string units) {
    return std::to_string(num) + units;
}