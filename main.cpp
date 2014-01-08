#include "fpm/fpm.h"
#include "logger/log.h"

int main(int argc, char* const argv[])
{
    Fpm *fpm = new Fpm();
    fpm->runServer();

    return 0;
}