#include "file.h"

bool File::Exists(std::string fileName) {
    std::fstream file(fileName);
    return(file.good());
}

std::string File::Read(std::string fileName) {
    std::fstream file(fileName);
    std::string temp = "";
    std::string result = "";
    if(file.is_open()) {
        while(file) {
            std::getline(file, temp);
            file.eof() ? result.append(temp) : result.append(temp + '\n');
            temp = "";
        }
    }
    file.close();
    return result;
}

std::string File::ReadBlock(std::string fileName, size_t blockSize) {
    std::string source = File::Read(fileName);
    if(source.length() == 0) {
        return "";
    }
    
    std::string output_str = "";
    int blocksNeeded = (source.length() <= blockSize) ? 1 : source.length() / blockSize + 1;

    for(int i = 0; i < blocksNeeded; i++) {
        int start = i * blockSize;
        
        std::string temp = source.substr(start, blockSize);
        if(temp.length() < blockSize) {
            int padAmount = blockSize - temp.length();
            temp.append(padAmount, '\x81');
        }

        output_str.append(temp);
    }
   
    return output_str;
}

void File::Write(std::string fileName, std::string data) {
    std::fstream file(fileName, std::fstream::out | std::fstream::trunc);
    
    if(file.is_open()) {
        file.write(data.c_str(), data.length());
    }
    file.close();
}

std::string File::RemovePadding(std::string source) {
    std::string temp = source;
    for(size_t i = 0; i < temp.length(); i++) {
        if(temp[i] == '\x81') {
            temp = temp.erase(i);
        }
    }
    return temp;
}