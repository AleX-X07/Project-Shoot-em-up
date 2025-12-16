#include "Bullet.h"
#include "Enemy.h"

Bullet::Bullet() {
    
}

Bullet::Bullet(float startX, float startY, float velX, float velY, int width, int height, SDL_Color col)
    : x(startX), y(startY), vx(velX), vy(velY), w(width), h(height), color(col) {
    x = startX;
    y = startY;
    vx = velX;
    vy = velY;
    w = width;
    h = height;
    color = col;
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

void Bullet::updateBullets(float dt) {
    for (auto& b : bullets) {
        b.x += b.vx * dt;
        b.y += b.vy * dt;
    }
}

void Bullet::BulletCollide(std::vector<Bullet>& bullets, std::vector<Enemy>& enemies) {
    std::vector<int> bulletErase;
    for (int i = bullets.size() - 1; i >= 0; i--) {
        SDL_FRect rect = { bullets[i].x, bullets[i].y , bullets[i].w, bullets[i].h };
        for (auto& e : enemies) {
            if (SDL_HasRectIntersectionFloat(&rect, &e.rect)) {
                bulletErase.push_back(i);
                break;
            }
        }
    }
    for (int i = bulletErase.size() - 1; i >= 0; i--) {
        bullets.erase(bullets.begin() + bulletErase[i]);
    }
}