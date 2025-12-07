#include <SDL3/SDL.h>
#include <vector>
#include "Bullet.h"
#include <SDL3_image/SDL_image.h>

class Entity {
public:
    SDL_FRect rect;
    SDL_Texture* texture;
    SDL_Color color;
    float speed;
    SDL_Texture* bulletTexture;
    std::vector<Bullet> bullets;
    float shootCooldown = 0.15f;      
    float timeSinceLastShot = 0.0f;
	int HP = 3;

    Entity(float x, float y, float w, float h, float spd = 200.0f);
    Entity(float x, float y, float w, float h, SDL_Texture* tex, float spd = 200.0f);
    Entity(float x, float y, float w, float h, SDL_Color col, float spd = 200.0f);

    void move(float dx, float dy, float dt);
    void clampToScreen(int screenWidth, int screenHeight);
    void render(SDL_Renderer* renderer);
    void loadTexture(SDL_Renderer* renderer, const char* filepath);
    void handleInput(const bool* keys, float dt);
	void shoot();
    void updateBullets(float dt);
	void renderBullets(SDL_Renderer* renderer);
    void loadBulletTexture(SDL_Renderer* renderer, const char* filepath);
	void DisplayHP(SDL_Renderer* renderer, int HP);

    ~Entity();
};