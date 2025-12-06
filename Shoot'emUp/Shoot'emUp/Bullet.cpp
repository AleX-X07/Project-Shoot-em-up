#include "Bullet.h"

 Bullet::Bullet(float startX, float startY, float velX, float velY, int width, int height, SDL_Texture* tex)
    : x(startX), y(startY), vx(velX), vy(velY), w(width), h(height), texture(tex) {
}

void Bullet::update(float dt) {
    x += vx * dt;
    y += vy * dt;
}

void Bullet::render(SDL_Renderer* renderer) {
    SDL_FRect dst = { x, y, (float)w, (float)h };
    SDL_RenderTexture(renderer, texture, NULL, &dst);
}
