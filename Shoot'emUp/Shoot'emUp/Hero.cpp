#include "Hero.h"

Entity::Entity(float x, float y, float w, float h, float spd)
    : rect{ x, y, w, h }, texture(nullptr), color{ 255, 255, 255, 255 }, speed(spd) {
}

Entity::Entity(float x, float y, float w, float h, SDL_Texture* tex, float spd)
    : rect{ x, y, w, h }, texture(tex), color{ 255, 255, 255, 255 }, speed(spd) {
}

Entity::Entity(float x, float y, float w, float h, SDL_Color col, float spd)
    : rect{ x, y, w, h }, texture(nullptr), color(col), speed(spd) {
}

void Entity::move(float dx, float dy, float dt) {
    rect.x += dx * speed * dt;
    rect.y += dy * speed * dt;
}

void Entity::clampToScreen(int screenWidth, int screenHeight) {
    if (rect.x < 0) rect.x = 0;
    if (rect.y < 0) rect.y = 0;
    if (rect.x + rect.w > screenWidth) rect.x = screenWidth - rect.w;
    if (rect.y + rect.h > screenHeight) rect.y = screenHeight - rect.h;
}

void Entity::render(SDL_Renderer* renderer) {
    if (texture) {
        SDL_RenderTexture(renderer, texture, NULL, &rect);
    }
    else {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);
    }
}

void Entity::loadTexture(SDL_Renderer* renderer, const char* filepath) {
    SDL_Surface* surface = IMG_Load(filepath);
    if (surface) {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
    }
    else {
        SDL_Log("Erreur chargement texture: %s", SDL_GetError());
    }
}

void Entity::handleInput(const bool* keys, float dt) {
    float dx = 0, dy = 0;
    if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W]) dy -= 1;
    if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S]) dy += 1;
    if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]) dx -= 1;
    if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]) dx += 1;
    move(dx, dy, dt);
}

Entity::~Entity() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}