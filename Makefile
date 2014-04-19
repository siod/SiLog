# Compiler to use

CC=g++
CFLAGS=-std=c++11 -fno-exceptions -Wall -Wextra

all: SiLog.lib
#$(CC)  $(CFLAGS) -c logging.o -o SiLog.lib

test: SiLog.lib
	$(CC) -DCONF_TEST $(CFLAGS) SiLog.lib logging_test.cpp -o tests.o

SiLog.lib: logging.cpp
	$(CC) $(CFLAGS) -c logging.cpp -o SiLog.lib


clean:
	rm -rf *.o
	rm -rf *.lib

