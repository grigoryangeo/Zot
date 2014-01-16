#include "modules/fpm/fpm.h"
#include "modules/zot/Core/appKernel.h"

const char* initilize()
{
	AppKernel *appKernel = new AppKernel("prod", false);
	
	return appKernel->Handle();

}


int main(int argc, char* const argv[])
{
	const char* (*request_handler)();
	Fpm *fpm = new Fpm();

	request_handler=&initilize;
	fpm->request_handler=request_handler;
    fpm->runServer();

    return 0;
}