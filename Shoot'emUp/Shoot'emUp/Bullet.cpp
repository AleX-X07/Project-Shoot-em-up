#include "Bullet.h"
#include "Enemy.h"

Bullet::Bullet() {
    
}

Bullet::Bullet(float startX, float startY, float velX, float velY, int width, int height, SDL_Color col)
    : x(startX), y(startY), vx(velX), vy(velY), w(width), h(height), color(col) {
}

void Bullet::renderBullets(SDL_Renderer* renderer, std::vector<Bullet>& bullets) {
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

void Bullet::updateBullets(float dt, std::vector<Bullet>& bullets) {
    for (auto& b : bullets) {
        b.x += b.vx * dt;
        b.y += b.vy * dt;
    }
}

void Bullet::exploseBullet(int windowWidth, std::vector<Bullet>& enemiesbullets) {
    std::vector<Bullet> newBullets; // Balles temporaires

    for (int i = enemiesbullets.size() - 1; i >= 0; i--) {
        // Vérifier si la balle doit exploser
        if (enemiesbullets[i].shouldExplose && enemiesbullets[i].x < windowWidth / 2) {

            // Sauvegarder la position d'explosion
            float explodeX = enemiesbullets[i].x;
            float explodeY = enemiesbullets[i].y;

            // Supprimer la balle originale
            enemiesbullets.erase(enemiesbullets.begin() + i);

            // Créer 5 balles d'explosion
            for (int j = 0; j < 5; j++) {
                Bullet explosionBullet;
                explosionBullet.x = explodeX;
                explosionBullet.y = explodeY;
                explosionBullet.w = 25;
                explosionBullet.h = 25;
                explosionBullet.vx = -300;
                explosionBullet.vy = -300 + (j * 150); // -300, -150, 0, 150, 300
                explosionBullet.color = { 255, 100, 0, 255 };
                explosionBullet.shouldExplose = false;
                newBullets.push_back(explosionBullet);
            }
        }
    }

    // Ajouter toutes les balles d'explosion
    for (auto& b : newBullets) {
        enemiesbullets.push_back(b);
    }
}