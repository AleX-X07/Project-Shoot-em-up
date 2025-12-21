#pragma once
#include <string>
#include <fstream>

class FileManager
{
    std::string filepath;

public:
    FileManager(const std::string& path);

    // Lire un nombre (score)
    int readInt();

    // Écrire un nombre (score)
    void writeInt(int value);

    ~FileManager();
};