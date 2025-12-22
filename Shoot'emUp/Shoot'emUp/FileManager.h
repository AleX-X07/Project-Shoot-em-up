#pragma once
// Librairie externe
#include <string>
#include <fstream>
#include <vector>

// Class FileManager for file .txt
class FileManager
{

public:

    // Filepath for 3 file : OrderLevel, Level 1 and level 2
    std::string filepath;
    std::string level_1;
    std::string level_2;
    
    // Constructor
    FileManager(const std::string& path);

    // Function for read OrderLevel
    void readOrderLevel();

    // Function for read Level
    void readIntLevel(int& nbr_enemy, int& nbr_shooter, int& nbr_shooter_V2, int& nbr_boss);
};