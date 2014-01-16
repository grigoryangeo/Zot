#pragma once
#include <string>
#include <stdlib.h>
#include <pthread.h>
#include "fcgi_stdio.h"

#include "../logger/log.h"
#include "../../conf/config.h"

#pragma comment(lib, "libfcgi.lib")


class Fpm {
    public:
        void runServer();
        Fpm();
		const char* (*request_handler)(); // функция обработчик

    protected:
        static void * runThread(void *a);

        int socketId;
        FCGX_Stream *in, *out, *err;
        FCGX_ParamArray envp;
        FCGX_Request request;
};