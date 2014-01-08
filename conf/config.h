#pragma once
#include <string>

class config {
    public:
        static const std::string PORT;  //Задаем номер порта TCP
        static const std::string SOCKET_PATH;  //Путь к сокету
        static const int LISTEN_QUEUE;   //Глубина стека запросов
        static const int THREAD_COUNT;   //Кол-во потоков
};