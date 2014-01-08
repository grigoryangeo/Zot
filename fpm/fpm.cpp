#include "fpm.h"

Fpm::Fpm()
{
    this->configure();
}

void Fpm::setPort(std::string port)
{
    this->port = port;
}


void Fpm::setlistenQueue(int listenQueue)
{
    this->listenQueueBacklog = listenQueue;
}


void Fpm::configure()
{
    this->setPort(":9000");
    this->setlistenQueue(400);
}

void Fpm::runServer()
{
    Log::addConsole("Start server", "green");

    FCGX_Stream *in, *out, *err;
    FCGX_ParamArray envp;

    //Инициализируем библиотеку перед работой.
    if(FCGX_Init())
        exit(1);

    int  listen_socket = FCGX_OpenSocket(this->port.c_str(), this->listenQueueBacklog); //Открываем новый слушающий сокет

    if(listen_socket < 0)
        exit(1);


    //Инициализируем структуру запроса
    if(FCGX_InitRequest(&this->request,  listen_socket, 0)) 
        exit(1);

    while(FCGX_Accept_r(&this->request) == 0)
    {
        FCGX_FPrintF(this->request.out, "Content-type: text/html\r\n\r\n<TITLE>fastcgi</TITLE>\n<H1>Hello world!!!</H1>\n");

        FCGX_Finish_r(&this->request);//Завершаем запрос
    }
}
