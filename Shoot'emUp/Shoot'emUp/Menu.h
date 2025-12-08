#pragma once
#include <SDL3/SDL.h>

struct MyStruct
{
    SDL_Texture* texture;
    SDL_Rect rect;
    bool selected;
}; 