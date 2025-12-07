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

    timeSinceLastShot += dt;
    if (keys[SDL_SCANCODE_SPACE] && timeSinceLastShot >= shootCooldown) {
        shoot();
        timeSinceLastShot = 0.0f;
    }
    move(dx, dy, dt);
}

void Entity::shoot() {
        /*if (bulletTexture) {
        bullets.emplace_back(rect.x + rect.w / 2 - 5, rect.y, 0, -400, 10, 20, bulletTexture);
		}*/
        bullets.emplace_back(rect.x + rect.w, rect.y + rect.h / 2 - 5, 800, 0, 40, 10, SDL_Color{ 0, 0, 255, 255 });
}

void Entity::loadBulletTexture(SDL_Renderer* renderer, const char* filepath) {
    SDL_Surface* surface = IMG_Load(filepath);
    if (surface) {
        bulletTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
    }
    else {
        SDL_Log("Erreur chargement bullet: %s", SDL_GetError());
    }
}

void Entity::updateBullets(float dt) {
    for (auto& b : bullets) b.update(dt);
    //// Optionnel : supprimer les balles hors écran
    //bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
    //    [](Bullet& b) { return b.x > 800 || b.x < 0 || b.y > 600 || b.y < 0; }),
    //    bullets.end());
}

void Entity::renderBullets(SDL_Renderer* renderer) {
    for (auto& b : bullets) b.render(renderer);
}

void Entity::DisplayHP(SDL_Renderer* renderer, int HP) {
    for (int i = 0; i < HP; ++i) {
        SDL_FRect hpRect = { 10.0f + i * 35.0f, 10.0f, 30.0f, 30.0f };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &hpRect);
    }
}

Entity::~Entity() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}