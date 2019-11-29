Client_UDP: Client_UDP.cpp Solicitud.o
	g++ Client_UDP.cpp Solicitud.o SocketDatagrama.o PaqueteDatagrama.o -o Client_UDP -lpthread
Solicitud.o: ../../Libraries/Solicitud.cpp SocketDatagrama.o ../../Libraries/Solicitud.h
	g++ ../../Libraries/Solicitud.cpp -c
SocketDatagrama.o: ../../Libraries/SocketDatagrama.cpp PaqueteDatagrama.o ../../Libraries/SocketDatagrama.h
	g++ ../../Libraries/SocketDatagrama.cpp -c
PaqueteDatagrama.o: ../../Libraries/PaqueteDatagrama.cpp ../../Libraries/PaqueteDatagrama.h
	g++ ../../Libraries/PaqueteDatagrama.cpp -c
