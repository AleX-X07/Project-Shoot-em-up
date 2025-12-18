#include "Shooter_Enemy.h"
#include "Enemy.h"
#include "Bullet.h"

class ShootMultiple_Enemy : public Enemy {
public:
    Uint32 lastShotTime;
    Uint32 lastSpawnTime = 0;
    Uint32 now = SDL_GetTicks();

    ShootMultiple_Enemy();
    ShootMultiple_Enemy(float px, float py, float pw, float ph, float ps);

    void update(int windowWidth);
    void shoot(std::vector<Bullet>& bullets, Uint32 now);
    void render(SDL_Renderer* renderer);
    static void spawnShootMultiple_Enemy(std::vector<ShootMultiple_Enemy>& triples, int windowWidth, int windowHeight);
};