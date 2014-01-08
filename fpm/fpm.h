#pragma once
#include <string>

#include "fcgi_stdio.h"
#include <stdlib.h>
#pragma comment(lib, "libfcgi.lib")

#include "../logger/log.h"

class Fpm {
    public:
        void setPort(std::string port);
        void setlistenQueue(int listenQueueBacklog);

        void runServer();
        Fpm();

    protected:
        void configure();

    private:
        std::string port;           //Задаем номер порта TCP
        int  listenQueueBacklog;    //Глубина стека запросов

        FCGX_Stream *in, *out, *err;
        FCGX_ParamArray envp;
        FCGX_Request request;
};