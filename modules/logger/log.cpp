#include "log.h"

void Log::addConsole(std::string message, std::string color)
{
    if(color=="white")
        message="\x1b[37m"+message+"\x1b[0m";

    if(color=="yellow")
        message="\x1b[33m"+message+"\x1b[0m";

    if(color=="green")
        message="\x1b[32m"+message+"\x1b[0m";

    if(color=="red")
        message="\x1b[31m"+message+"\x1b[0m";

    std::cout << message << "\n";
}