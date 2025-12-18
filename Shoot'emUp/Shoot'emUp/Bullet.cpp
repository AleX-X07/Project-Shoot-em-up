#include "Bullet.h"
#include "Enemy.h"

Bullet::Bullet() {
    
}

Bullet::Bullet(float startX, float startY, float velX, float velY, int width, int height, SDL_Color col)
    : x(startX), y(startY), vx(velX), vy(velY), w(width), h(height), color(col) {
}

void Bullet::renderBullets(SDL_Renderer* renderer) {
    for (auto& b : bullets) {
        SDL_FRect dst = { b.x, b.y, (float)b.w, (float)b.h };
        if (b.bulletTexture) {
            SDL_RenderTexture(renderer, b.bulletTexture, NULL, &dst);
        }
        else {
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(renderer, &dst);
        }
    } 
}

void Bullet::loadBulletTexture(SDL_Renderer* renderer, const char* filepath) {
    SDL_Surface* surface = IMG_Load(filepath);
    if (surface) {
        bulletTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
        SDL_SetTextureScaleMode(bulletTexture, SDL_SCALEMODE_NEAREST);
    }
    else {
        SDL_Log("Erreur chargement bullet: %s", SDL_GetError());
    }
}

void Bullet::updateBullets(float dt) {
    for (auto& b : bullets) {
        b.x += b.vx * dt;
        b.y += b.vy * dt;
    }
}