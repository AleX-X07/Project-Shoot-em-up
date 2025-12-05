#ifndef ENTITY_H
#define ENTITY_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class Entity {
public:
    SDL_FRect rect;
    SDL_Texture* texture;
    SDL_Color color;
    float speed;

    Entity(float x, float y, float w, float h, float spd = 200.0f);
    Entity(float x, float y, float w, float h, SDL_Texture* tex, float spd = 200.0f);
    Entity(float x, float y, float w, float h, SDL_Color col, float spd = 200.0f);

    void move(float dx, float dy, float dt);
    void clampToScreen(int screenWidth, int screenHeight);
    void render(SDL_Renderer* renderer);
    void loadTexture(SDL_Renderer* renderer, const char* filepath);
    void handleInput(const bool* keys, float dt);

    ~Entity();
};

#endif