#include "../headers/helper.h"

SDL_Rect helper::renderText(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, std::string s, int x, int y) {
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
    return dest;
}

std::string helper::formatString(double num, std::string units) {
    return std::to_string(num) + units;
}

void helper::renderStackedText(SDL_Renderer *renderer, TTF_Font* font, SDL_Color color, std::vector<std::string> text, int x, int _y, int padding)
{
    int y = _y;
    for (int i = 0; i < text.size(); i++) {
        SDL_Rect r = renderText(renderer, font, color, text[i], x, y);
        y += r.h + padding;
    }
}
