CC=g++
CFLAGS=-I/usr/local/include -L/usr/local/lib -lfcgi
LDFLAGS=
SOURCES=main.cpp modules/fpm/fpm.cpp modules/logger/log.cpp conf/config.cpp modules/zot/Core/appKernel.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=build/site

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

clean:
	rm -rf *.o $(EXECUTABLE)