all: client server
client: client.c game.h communicate.h
	gcc client.c -o client
server: server.c game.h communicate.h
	gcc server.c -o server -pthread
clean:
	rm -f *.o client
	rm -f *.o server
