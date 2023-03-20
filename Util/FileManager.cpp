//
// Created by ernes on 10.01.2023.
//

#include "FileManager.h"

FileManager::FileManager(std::string filename)
    :_filename(filename)
{
}

void FileManager::writeLine(const std::string& stringToWrite) {
    std::ofstream file(_filename);
    file << stringToWrite << std::endl;
}
