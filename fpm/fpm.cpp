#include "fpm.h"

Fpm::Fpm()
{
}

void* Fpm::runThread(void *a)
{
    Log::addConsole("Request start","green");

    Fpm* fpm = (Fpm *)a;
    int rc, i;
    FCGX_Request request=fpm->request;
    char *server_name;
    int socketId=fpm->socketId;

    //Инициализируем структуру запроса
    if(FCGX_InitRequest(&fpm->request, fpm->socketId, 0) != 0)
    {
        //ошибка при инициализации структуры запроса
        Log::addConsole("Can not init request", "red");
        return NULL;
    }

    for(;;)
    {
        static pthread_mutex_t accept_mutex = PTHREAD_MUTEX_INITIALIZER;

        //попробовать получить новый запрос
        Log::addConsole("Try to accept new request","yellow");

        pthread_mutex_lock(&accept_mutex);
        rc = FCGX_Accept_r(&request);
        pthread_mutex_unlock(&accept_mutex);
        
        if(rc < 0)
        {
            //ошибка при получении запроса
            Log::addConsole("Can not accept new request","red");
            break;
        }
        Log::addConsole("request is accepted","green");

        //получить значение переменной
        server_name = FCGX_GetParam("SERVER_NAME", request.envp);
        
        //вывести все HTTP-заголовки (каждый заголовок с новой строки)
        FCGX_PutS("Content-type: text/html\r\n", request.out);
        //между заголовками и телом ответа нужно вывести пустую строку
        FCGX_PutS("\r\n", request.out);
        //вывести тело ответа (например - html-код веб-страницы)
        FCGX_PutS("<html>\r\n", request.out);
        FCGX_PutS("<head>\r\n", request.out);
        FCGX_PutS("<title>FastCGI Hello! (multi-threaded C, fcgiapp library)</title>\r\n", request.out);
        FCGX_PutS("</head>\r\n", request.out);
        FCGX_PutS("<body>\r\n", request.out);
        FCGX_PutS("<h1>FastCGI Hello! (multi-threaded C, fcgiapp library)</h1>\r\n", request.out);
        FCGX_PutS("<p>Request accepted from host <i>", request.out);
        FCGX_PutS(server_name ? server_name : "?", request.out);
        FCGX_PutS("</i></p>\r\n", request.out);
        FCGX_PutS("</body>\r\n", request.out);

        //char* content=get_web_data();
        //FCGX_PutS(content, request.out);

        FCGX_PutS("</html>\r\n", request.out);


        //"заснуть" - имитация многопоточной среды
        //sleep(0.5);
        
        //закрыть текущее соединение
        FCGX_Finish_r(&request);

        Log::addConsole("Request finish","green");
    }

    return NULL;
}


void Fpm::runServer()
{
    int i;

    std::string port=config::PORT;
    int listenQueueBacklog=config::LISTEN_QUEUE;
    int thread_count=config::THREAD_COUNT;
    std::string socket_path=config::SOCKET_PATH;

    pthread_t id[thread_count];

    Log::addConsole("Start server", "green");

    FCGX_Stream *in, *out, *err;
    FCGX_ParamArray envp;

    //Инициализируем библиотеку перед работой.
    if(FCGX_Init())
    {
        Log::addConsole("Cant init Libiry", "red");
        exit(1);
    }

    //Открываем новый слушающий сокет
    this->socketId = FCGX_OpenSocket(port.c_str(), listenQueueBacklog);

    if(this->socketId < 0)
    {
        Log::addConsole("Cant open socket", "red");
        exit(2);
    }


    //создаём рабочие потоки
    for(i = 0; i < thread_count; i++)
    {
        pthread_create(&id[i], NULL, this->runThread, this);
    }

    //Блокируем основной процесс. Ждем завершения рабочих потоков
    for(i = 0; i < thread_count; i++)
    { 
        pthread_join(id[i], NULL);
    } 
}
