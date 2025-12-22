// Load file
#include "Hero.h"
#include "Enemy.h"

// Constructor
Hero::Hero() {

}

Hero::Hero(float x, float y, float w, float h, float _speed) {
    rect = { x, y, w, h };
    speed = _speed;
}

// Function for lock player in the window
void Hero::clampToScreen(int screenWidth, int screenHeight) { 
    if (rect.x < 0) {
        rect.x = 0;
    }
    if (rect.y < 0) {
        rect.y = 0;
    }
    if (rect.x + rect.w > screenWidth) {
        rect.x = screenWidth - rect.w;
    }
    if (rect.y + rect.h > screenHeight) {
        rect.y = screenHeight - rect.h;
    }
}

// Render of player
void Hero::render(SDL_Renderer* renderer) { 
    // If texture existe, dispaly sprite. Else, display cube 
    if (texture) {
        SDL_RenderTexture(renderer, texture, NULL, &rect);
    }
    else {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
}

// Update of hero, depending on input
void Hero::updateInput(const bool* keys, float dt) { 
    float dx = 0, dy = 0;
    // Chek if z,q,s,d or up,down,left,right are pressed
    if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W]) {
        dy -= 1;
    }
    if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S]) {
        dy += 1;
    }
    if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]) {
        dx -= 1;
    }
    if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]) {
        dx += 1;
    }
    // Check the time for delay of 0.15 between each bullet
    timeSinceLastShot += dt;
    if (keys[SDL_SCANCODE_SPACE] && timeSinceLastShot >= shootCooldown) {
        shoot();
        timeSinceLastShot = 0.0f;
    }
    // Update position of player
    rect.x += dx * speed * dt;
    rect.y += dy * speed * dt;
}

// Function for shoot
void Hero::shoot() {
        // Create bullet
        Bullet newBullet(rect.x + rect.w, rect.y + rect.h / 2 - 30, 800, 0, 120, 60);
        newBullet.bulletTexture = bulletTexture;
        heroBullets.push_back(newBullet); // Put the bullet in the vector bullet
}

// Function for display HUD
void Hero::HUD(SDL_Renderer* renderer, SDL_Texture* texture, int HP, int Score) {
    // Display heart side by side
    for (int i = 0; i < HP; ++i) {
        SDL_FRect hpRect = { 10.0f + i * 35.0f, 10.0f, 30, 30 };
        // If texture existe, display heart. Else, display cube color
        if (texture) {
            SDL_RenderTexture(renderer, texture, NULL, &hpRect);
        }
        else {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
            SDL_RenderFillRect(renderer, &hpRect);
        }
    }
    // Display score under hearts
    TTF_Font* font = TTF_OpenFont("assets/arialmt.ttf", 24);
    if (font) {
        std::string scoreText = "Score: " + std::to_string(Score);
        SDL_Color white = { 255, 255, 255, 255 };
        size_t size = scoreText.size();
        SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(), size, white);
        if (scoreSurface) {
            SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
            SDL_FRect scoreRect = { 10.0f, 50.0f, (float)scoreSurface->w, (float)scoreSurface->h };
            SDL_RenderTexture(renderer, scoreTexture, NULL, &scoreRect);
            SDL_DestroyTexture(scoreTexture);
            SDL_DestroySurface(scoreSurface);
        }
        TTF_CloseFont(font);
    }
}

// Function for check collision between enemy and bullet player
void Hero::CollideBullet(std::vector<Enemy>& enemies) { 

    // Create vector of bool for bullet and enemy to remove
    std::vector<bool> bulletToRemove(heroBullets.size(), false);
    std::vector<bool> enemyToRemove(enemies.size(), false);

    // If bullet have collide with enemies, enemies lost HP
    for (int i = 0; i < heroBullets.size(); i++) {
        SDL_FRect rect = { heroBullets[i].x, heroBullets[i].y, heroBullets[i].w, heroBullets[i].h };

        for (int j = 0; j < enemies.size(); j++) {
            if (SDL_HasRectIntersectionFloat(&rect, &enemies[j].rect)) {
                bulletToRemove[i] = true;
                enemies[j].HP--;

                // If HP enemmies == 0, change bool in the vector ToRemove, increase score and increase bossDeath if it's boss, else nbr_enemy_death
                if (enemies[j].HP <= 0) {
                    enemyToRemove[j] = true;
                    score += enemies[j].Value;
                    if (enemies[j].numEnemy == 10) {
                        bossDeath++;
                    }
                    else {
                        nbr_enemy_death++;
                    }
                }
                break;
            }
        }
    }

    // Remove heroBullets who are true in the ToRemove vector
    for (int i = heroBullets.size() - 1; i >= 0; i--) {
        if (bulletToRemove[i]) {
            heroBullets.erase(heroBullets.begin() + i);
        }
    }

    // Remove enemies who are true in the ToRemove vector
    for (int i = enemies.size() - 1; i >= 0; i--) {
        if (enemyToRemove[i]) {
            enemies.erase(enemies.begin() + i);
        }
    }
}

// Function for check collision between hero and enemies
void Hero::CollideEnemy(std::vector<Enemy>& enemies, float dt) {
    // Check cooldown
    timeSinceLastHit += dt;
    if (timeSinceLastHit >= collisionCooldownEnemy) {
        timeSinceLastHit = 0;
        for (auto& e : enemies) {
            // If collision, player - 1 HP
            if (SDL_HasRectIntersectionFloat(&rect, &e.rect)) {
                HP--;
                break;
            }
        }
    }
}

// Function for check collision between player and enemies bullets
void Hero::CollideEnemyBullet(std::vector<Enemy>& enemies, float dt) {
    timeSinceLastHitBullet += dt;
    if (timeSinceLastHitBullet >= collisionCooldownBulletEnemy) {
        for (auto& e : enemies) {
            for (int i = e.enemiesBullet.size() - 1; i >= 0; i--) {
                SDL_FRect bulletRect = { e.enemiesBullet[i].x, e.enemiesBullet[i].y, e.enemiesBullet[i].w, e.enemiesBullet[i].h };
                // If collide, player - 1 HP and enemies bullet is erase
                if (SDL_HasRectIntersectionFloat(&rect, &bulletRect)) {
                    HP--;
                    e.enemiesBullet.erase(e.enemiesBullet.begin() + i);
                    timeSinceLastHitBullet = 0;
                    break;
                }
            }
        }
    }
}
