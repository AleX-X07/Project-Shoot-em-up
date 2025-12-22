#include "FileManager.h"

FileManager::FileManager(const std::string& path) : filepath(path) {
}

void FileManager::readOrderLevel() {
    std::ifstream file(filepath);
    int level1 = 0;
    int level2 = 0;
    if (file.is_open()) {
        file >> level1;
        file >> level2;
        file.close();
    }
    if (level1 == 1) {
        level_1 = "Level/Level1.txt";
        level_2 = "Level/Level2.txt";
    }
    else {
        level_1 = "Level/Level2.txt";
        level_2 = "Level/Level1.txt";
    }
}

void FileManager::readIntLevel(int& nbr_enemy, int& nbr_shooter, int& nbr_shooter_V2, int& nbr_boss) {
    std::ifstream file(filepath);

    if (file.is_open()) {
        file >> nbr_enemy;
        file >> nbr_shooter;
        file >> nbr_shooter_V2;
        file >> nbr_boss;
        file.close();
    }
}

FileManager::~FileManager() {
}