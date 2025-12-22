// Load file
#include "Level.h"
#include "Enemy.h"
#include "Item.h"

// Constructor
Level::Level() {
    numLevel = 1;
	nbr_enemy = 0;
	nbr_shooter = 0;
	nbr_shooter_V2 = 0;
	nbr_boss = 0;
	levelWithBoss = false;
    nbr_enemy_total = nbr_enemy;
    nbr_shooter_total = nbr_shooter;
    nbr_shooter_V2_total = nbr_shooter_V2;
    nbr_boss_total = nbr_boss;
}

// Function for set level
void Level::setMyLevel(int _nbr_enemy, int _nbr_shooter, int _nbr_shooter_V2, int _nbr_boss) {
	nbr_enemy = _nbr_enemy;
	nbr_shooter = _nbr_shooter;
	nbr_shooter_V2 = _nbr_shooter_V2;
	nbr_boss = _nbr_boss;
    // Chek if the level have a boss
	if (_nbr_boss > 0) {
		levelWithBoss = true;
	}
    nbr_enemy_total = _nbr_enemy;
    nbr_shooter_total = _nbr_shooter;
    nbr_shooter_V2_total = _nbr_shooter_V2;
    nbr_boss_total = _nbr_boss;
}

// Function for the winCondition
int Level::typeLevel(Hero& player) {
	if (levelWithBoss) {
        // If the level have boss, you need to kill the boss
		if (player.bossDeath == nbr_boss_total) {
            levelWithBoss = false;
			return 1;
		}
	}
	else {
        // If the level don't have boss, you need to kill all enemies
		if (player.nbr_enemy_death == (nbr_enemy_total + nbr_shooter_total + nbr_shooter_V2_total)) {
			return 1;
		}
	}
	return 0;
}

// Function for display level
void Level::displayLevel(SDL_Renderer* renderer, LoadRessource& MyRessource, Hero& player, float dt, SDL_Window* window, std::vector<Enemy>& enemies, std::vector<Bullet>& bullets, Level& MyLevel, const bool* keys, int w, int h, std::vector<Item>& item) {
    
    // Update player
    player.updateInput(keys, dt);
    player.clampToScreen(w, h);
    player.updateBullets(dt, player.heroBullets);

    // Spawn enemies
    spawnTimer += dt; 
    if (spawnTimer >= spawnInterval) {
        Enemy::EnemyManager(enemies, renderer, w, h, MyRessource, MyLevel);
        spawnTimer = 0;
    }

    // Spawn item
    spawnTimerItem += dt;
    if (spawnTimerItem >= spawnIntervalItem) {
        Item::itemSpawn(item, MyRessource.heart, w, h);
        spawnTimerItem = 0;
    }

    // Update imte/enemy
    Item::updateItem(item, dt);
    Enemy::updateEnemy(enemies, dt, w, h, player);

    // Enemies shoot
    for (auto& e : enemies) { 
        if (e.numEnemy == 2) {
            e.shoot(e.enemiesBullet);
        }
        else if (e.numEnemy == 3) {
            e.shootV2(e.enemiesBullet);
        }
        else if (e.numEnemy == 10) {
            e.shootBoss(e.enemiesBullet);
        }
    }

    // Display background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, MyRessource.backgroundLevel1, NULL, NULL);

    // Render
    player.render(renderer);
    player.renderBullets(renderer, player.heroBullets);
    Enemy::renderEnemy(renderer, enemies);
    Item::renderItem(renderer, item);
    player.HUD(renderer, MyRessource.heart, player.HP, player.score);

    // Check collisions
    player.CollideEnemy(enemies, dt);
    player.CollideEnemyBullet(enemies, dt);
    player.CollideBullet(enemies);
    Item::collidePlayer(item, player);

    // Display modification
    SDL_RenderPresent(renderer);
}

// Function for reset player between 2 level
void Level::reset(Hero& player, std::vector<Enemy>& enemies) {
    // Variable reset between 2 level
    player.HP = 4;
    player.heroBullets.clear();
    enemies.clear();
    player.rect.x = 400.0f;
    player.rect.y = 300.0f;
    spawnTimer = 0;     
}

// Function for restart à party
void Level::restart(Hero& player, Enemy& MyEnemy, Item& MyItem, Level& MyLevel, bool& restart) {
    // Variable reset for restart
    player.HP = 4;
    player.score = 0;
    player.nbr_enemy_death = 0;
    player.bossDeath = 0;
    player.heroBullets.clear();
    player.rect.x = 400.0f;
    player.rect.y = 300.0f;
    player.timeSinceLastShot = 0.0f;

    MyEnemy.enemies.clear();

    MyItem.itemVector.clear();

    numLevel = 0;
    spawnTimer = 0;
    spawnTimerItem = 0;
    levelWithBoss = false;

    // Re-open level for an other party
    FileManager _Level = FileManager("Level/orderLevel.txt");
    _Level.readOrderLevel();
    _Level = FileManager(_Level.level_1);
    _Level.readIntLevel(MyLevel.nbr_enemy, MyLevel.nbr_shooter,MyLevel.nbr_shooter_V2, MyLevel.nbr_boss);
    MyLevel.setMyLevel(MyLevel.nbr_enemy, MyLevel.nbr_shooter,MyLevel.nbr_shooter_V2, MyLevel.nbr_boss);

    restart = false;
}