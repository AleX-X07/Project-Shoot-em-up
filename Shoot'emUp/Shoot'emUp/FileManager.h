#pragma once
#include <string>
#include <fstream>
#include <vector>

class FileManager
{
    std::string filepath;
public:
    std::string level_1;
    std::string level_2;

    FileManager(const std::string& path);

    void readOrderLevel();
    void readIntLevel(int& nbr_enemy, int& nbr_shooter, int& nbr_shooter_V2, int& nbr_boss);

    ~FileManager();
};