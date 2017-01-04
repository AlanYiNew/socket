CC=g++
CFLAGS=-Wall -Werror -Os -o 


server: main.o server.o
	$(CC) main.o server.o  $(CFLAGS) server 

server.o:server.cpp server.h

main.o:main.cpp

client: client.o
	$(CC) client.o $(CFLAGS) client

client.o:client.cpp

.PHONY:clean

clean:
	rm *.o
