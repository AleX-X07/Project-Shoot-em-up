#include "FileManager.h"

FileManager::FileManager(const std::string& path) : filepath(path) {
}

int FileManager::readInt() {
    std::ifstream file(filepath);
    int value = 0;

    if (file.is_open()) {
        file >> value;
        file.close();
    }

    return value;
}

void FileManager::writeInt(int value) {
    std::ofstream file(filepath);

    if (file.is_open()) {
        file << value;
        file.close();
    }
}

FileManager::~FileManager() {
}