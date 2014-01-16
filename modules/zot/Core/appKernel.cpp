#include "AppKernel.h"

AppKernel::AppKernel(std::string environment, bool debug)
{
}

const char* AppKernel::Handle()
{
    return "Content-type: text/html\r\n\r\n<TITLE>fastcgi</TITLE>\n<H1>Fastcgi: Hello world.</H1>\n";
}


void AppKernel::Handle2(char* r)
{

}