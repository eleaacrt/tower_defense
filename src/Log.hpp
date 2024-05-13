#pragma once
#include <iostream>
#include <string>

#define DEBUG_MODE true

class Log
{
public:
    static void Debug(const std::string &msg)
    {
        if (DEBUG_MODE)
            std::cout << "[Debug] " << msg << std::endl;
    }
    static void Error(const std::string &msg)
    {
        std::cout << "[Error] " << msg << std::endl;
    }
};
