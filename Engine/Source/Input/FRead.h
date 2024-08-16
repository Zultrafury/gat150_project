#pragma once
#include <fstream>
#include <string>

class FRead {
public:
    static std::string ReadFile(std::string filename)
    {
        std::string readbuff, buffer;
        std::ifstream File(filename);
        while (std::getline(File, readbuff))
        {
            buffer += readbuff;
        }
        File.close();
        return buffer;
    }
};
