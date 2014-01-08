#pragma once
#include <string>
#include <iostream>

class Log {
    public:
        static void addConsole(std::string message, std::string color="normal");
};