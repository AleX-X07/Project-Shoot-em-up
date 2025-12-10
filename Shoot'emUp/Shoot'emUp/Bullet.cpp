#include "Bullet.h"

 Bullet::Bullet(float startX, float startY, float velX, float velY, int width, int height, SDL_Color col)
    : x(startX), y(startY), vx(velX), vy(velY), w(width), h(height), color(col) {
}

void Bullet::update(float dt) {
    x += vx * dt;
    y += vy * dt;
}

void Bullet::render(SDL_Renderer* renderer) {
    SDL_FRect dst = { x, y, (float)w, (float)h };

    if (texture) {
        SDL_RenderTexture(renderer, texture, NULL, &dst);
    }
    else {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &dst);
    }
}
