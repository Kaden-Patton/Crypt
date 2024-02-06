#ifndef FILE_H
#define FILE_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

class File {
   // std::string file_contents;
    
    public:
    
    File() = default;
    static bool Exists(std::string fileName);
    static std::string Read(std::string fileName);
    static std::string ReadBlock(std::string fileName, size_t blockSize);
    static void Write(std::string fileName, std::string data);
    static std::string RemovePadding(std::string source);
};

#endif