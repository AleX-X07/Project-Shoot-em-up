// Load file
#include "Bullet.h"
#include "Enemy.h"

//Constructor
Bullet::Bullet() {
    
}

Bullet::Bullet(float startX, float startY, float velX, float velY, int width, int height) {
    x = startX;
    y = startY;
    vx = velX;
    vy = velY;
    w = width;
    h = height;
}

// Render/Update
void Bullet::renderBullets(SDL_Renderer* renderer, std::vector<Bullet>& bullets) {
    for (auto& b : bullets) {
        SDL_FRect dst = { b.x, b.y, (float)b.w, (float)b.h };
        // Display bullet texture if there is one 
        if (b.bulletTexture) {
            SDL_RenderTexture(renderer, b.bulletTexture, NULL, &dst);
        }
        else {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &dst);
        }
    } 
}

void Bullet::updateBullets(float dt, std::vector<Bullet>& bullets) {
    // Move the bullets en the 2 axe : x and y
    for (auto& b : bullets) {
        b.x += b.vx * dt;
        b.y += b.vy * dt;
    }
}

// For bullet who explode, they launch lots of other balls flying in all directions
void Bullet::exploseBullet(int windowWidth, std::vector<Bullet>& enemiesbullets) {
    // Vector temporary
    std::vector<Bullet> newBullets; 

    for (int i = enemiesbullets.size() - 1; i >= 0; i--) {
        // Check is the bullets explode. If the explode, explode in the middle of the window
        if (enemiesbullets[i].shouldExplode && enemiesbullets[i].x < windowWidth / 2) {

            // Save the position of the explosion
            float explodeX = enemiesbullets[i].x;
            float explodeY = enemiesbullets[i].y;

            // Erase enemies who explode
            enemiesbullets.erase(enemiesbullets.begin() + i);

            // Create five bullet in the explosion
            for (int j = 0; j < 5; j++) {
                Bullet e_Explode;
                e_Explode.x = explodeX;
                e_Explode.y = explodeY;
                e_Explode.w = 25;
                e_Explode.h = 25;
                e_Explode.vx = -300;
                e_Explode.vy = -300 + (j * 150);
                e_Explode.shouldExplode = false;
                newBullets.push_back(e_Explode);
            }
        }
    }

    // put the bullet in the vector
    for (auto& b : newBullets) {
        enemiesbullets.push_back(b);
    }
}