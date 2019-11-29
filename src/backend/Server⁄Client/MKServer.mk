Server_UDP: Server_UDP.cpp Respuesta.o
	g++ Server_UDP.cpp Respuesta.o SocketDatagrama.o PaqueteDatagrama.o -o Server_UDP
Respuesta.o: ../Libraries/Respuesta.cpp SocketDatagrama.o ../Libraries/Respuesta.h
	g++ ../Libraries/Respuesta.cpp -c
SocketDatagrama.o: ../Libraries/SocketDatagrama.cpp PaqueteDatagrama.o ../Libraries/SocketDatagrama.h
	g++ ../Libraries/SocketDatagrama.cpp -c
PaqueteDatagrama.o: ../Libraries/PaqueteDatagrama.cpp ../Libraries/PaqueteDatagrama.h
	g++ ../Libraries/PaqueteDatagrama.cpp -c
