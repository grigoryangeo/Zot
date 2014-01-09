#pragma once
#include "../../autoloader/autoloader.h"

class AppKernel {
    public:
        const char* Handle();
        AppKernel();

    private:
        int environment;
};