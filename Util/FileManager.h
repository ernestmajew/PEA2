#ifndef PEA2_FILEMANAGER_H
#define PEA2_FILEMANAGER_H
#include<iostream>
#include<fstream>

class FileManager {
public:
    FileManager(std::string filename);
    void writeLine(const std::string& stringToWrite);
private:
    std::string _filename;
};


#endif //PEA2_FILEMANAGER_H
