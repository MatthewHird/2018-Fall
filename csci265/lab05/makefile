CC=g++
Options=-Wall
ObjFlags=-c
Obj=obj/tcpServer.o obj/tcpClient.o obj/client.o obj/server.o obj/keyPress.o
Src=server/tcpServer.c client/tcpClient.c client/client.C server/server.C key/keyPress.C
Exe=bin/tcpServer bin/tcpClient bin/server bin/client

all: ${Exe} 

bin/tcpServer: obj/tcpServer.o
	${CC} ${Options} obj/tcpServer.o -o bin/tcpServer

bin/tcpClient: obj/tcpClient.o
	${CC} ${Options} obj/tcpClient.o -o bin/tcpClient

bin/server: obj/server.o obj/keyPress.o
	${CC} ${Options} obj/server.o obj/keyPress.o -o bin/server

bin/client: obj/client.o
	${CC} ${Options} obj/client.o -o bin/client

obj/tcpServer.o: server/tcpServer.c server/tcpServer.h
	${CC} ${Options} -c server/tcpServer.c -o obj/tcpServer.o

obj/tcpClient.o: client/tcpClient.c client/tcpClient.h
	${CC} ${Options} -c client/tcpClient.c -o obj/tcpClient.o

obj/client.o: client/client.C client/client.h
	${CC} ${Options} -c client/client.C -o obj/client.o

obj/server.o: server/server.C server/server.h
	${CC} ${Options} -c server/server.C -o obj/server.o

obj/keyPress.o: key/keyPress.C key/keyPress.h
	${CC} ${Options} -c key/keyPress.C -o obj/keyPress.o

clean:
	rm -f ${Obj}