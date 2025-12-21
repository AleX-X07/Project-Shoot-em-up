#include "Hero.h"
#include "Enemy.h"

Entity::Entity() {
    nbr_enemy_death = 0;
    bossDeath = 0;
}

Entity::Entity(float x, float y, float w, float h, SDL_Texture* tex, float spd) // Constructor with texture
    : rect{ x, y, w, h }, texture(tex), color{ 255, 255, 255, 255 }, speed(spd) {
}

Entity::Entity(float x, float y, float w, float h, SDL_Color col, float spd) // Constructor without texture
    : rect{ x, y, w, h }, texture(nullptr), color(col), speed(spd) {
}

void Entity::move(float dx, float dy, float dt) { // Function for move player
    rect.x += dx * speed * dt;
    rect.y += dy * speed * dt;
}

void Entity::clampToScreen(int screenWidth, int screenHeight) { // Function for lock player in the window
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

void Entity::render(SDL_Renderer* renderer) { // Function for display sprite of player
    if (texture) {
        SDL_RenderTexture(renderer, texture, NULL, &rect);
    }
    else {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);
    }
}

void Entity::handleInput(const bool* keys, float dt) { // Function for interation with the keyboard
    float dx = 0, dy = 0;
    if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W]) dy -= 1;
    if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S]) dy += 1;
    if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]) dx -= 1;
    if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]) dx += 1;

    timeSinceLastShot += dt;
    if (keys[SDL_SCANCODE_SPACE] && timeSinceLastShot >= shootCooldown) {
        shoot();
        timeSinceLastShot = 0.0f;
    }
    move(dx, dy, dt);
}

void Entity::shoot() { // Function for shoot
        Bullet newBullet(rect.x + rect.w, rect.y + rect.h / 2 - 30, 800, 0, 120, 60, SDL_Color{ 0, 0, 255, 255 });
        newBullet.bulletTexture = bulletTexture;
        heroBullets.push_back(newBullet);
}

void Entity::HUD(SDL_Renderer* renderer, SDL_Texture* texture, int HP, int Score) { // Function for display HUD
    for (int i = 0; i < HP; ++i) {
        SDL_FRect hpRect = { 10.0f + i * 35.0f, 10.0f, 30, 30 };
        if (texture) {
            SDL_RenderTexture(renderer, texture, NULL, &hpRect);
        }
        else {
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(renderer, &hpRect);
        }
    }
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

void Entity::CollideBullet(std::vector<Enemy>& enemies) { // Function for check collision

    std::vector<bool> bulletToRemove(heroBullets.size(), false);
    std::vector<bool> enemyToRemove(enemies.size(), false);

    for (int i = 0; i < heroBullets.size(); i++) {
        SDL_FRect rect = { heroBullets[i].x, heroBullets[i].y, heroBullets[i].w, heroBullets[i].h };

        for (int j = 0; j < enemies.size(); j++) {
            if (SDL_HasRectIntersectionFloat(&rect, &enemies[j].rect)) {
                bulletToRemove[i] = true;
                enemies[j].HP--;

                if (enemies[j].HP <= 0) {
                    enemyToRemove[j] = true;
                    Score += enemies[j].Value;
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

    for (int i = heroBullets.size() - 1; i >= 0; i--) {
        if (bulletToRemove[i]) {
            heroBullets.erase(heroBullets.begin() + i);
        }
    }

    for (int i = enemies.size() - 1; i >= 0; i--) {
        if (enemyToRemove[i]) {
            enemies.erase(enemies.begin() + i);
        }
    }
}

void Entity::CollideEnemy(std::vector<Enemy>& enemies, float dt) {
    timeSinceLastHit += dt;
    if (timeSinceLastHit >= collisionCooldownEnemy) {
        timeSinceLastHit = 0;
        for (auto& e : enemies) {
            if (SDL_HasRectIntersectionFloat(&rect, &e.rect)) {
                HP--;
                break;
            }
        }
    }
}

void Entity::CollideEnemyBullet(std::vector<Enemy>& enemies, float dt) {
    timeSinceLastHitBullet += dt;
    if (timeSinceLastHitBullet >= collisionCooldownBulletEnemy) {
        for (auto& e : enemies) {
            for (int i = e.enemiesBullet.size() - 1; i >= 0; i--) {
                SDL_FRect bulletRect = { e.enemiesBullet[i].x, e.enemiesBullet[i].y,
                                         e.enemiesBullet[i].w, e.enemiesBullet[i].h };
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

Entity::~Entity() {

}