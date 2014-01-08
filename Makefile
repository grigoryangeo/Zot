CC=g++
CFLAGS=-I/usr/local/include -L/usr/local/lib -lfcgi
LDFLAGS=
SOURCES=main.cpp fpm/fpm.cpp logger/log.cpp conf/config.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=site

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

fpm:
	$(CC) $(CFLAGS) fpm.cpp

clean:
	rm -rf *.o $(EXECUTABLE)