#pragma once
#include <string>

#include "fcgi_stdio.h"
#include <stdlib.h>
#include <pthread.h>
#pragma comment(lib, "libfcgi.lib")

#include "../autoloader/autoloader.h"

class Fpm {
    public:
        void runServer();
        Fpm();

    private:
        static void * runThread(void *a);
        
        int socketId;
        FCGX_Stream *in, *out, *err;
        FCGX_ParamArray envp;
        FCGX_Request request;
};