#pragma once
#include "../../autoloader/autoloader.h"

class AppKernel {
    public:
        const std::string VERSION;
        const std::string VERSION_ID;
        const std::string MAJOR_VERSION;
        const std::string MINOR_VERSION;
        const std::string RELEASE_VERSION;
        const std::string EXTRA_VERSION;

        AppKernel(std::string environment, bool debug);

        const char* Handle();
        static void Handle2(char* r);
        void* init();
        void* boot();
        void* terminate();
        void* shutdown();

        void* getEnvironment();
        void* isDebug();
        void* getName();
        void* getRootDir();
        void* getStartTime();
        void* getLogDir();

    protected:
        std::string environment;
        bool debug;
        std::string bundles;

        std::string bundleMap;
        std::string container;
        std::string rootDir;
        std::string booted;
        std::string name;
        std::string startTime;
        std::string loadClassCache;

    private:
};