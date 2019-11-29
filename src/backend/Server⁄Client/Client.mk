Client: Client.cpp Solicitud.o
	g++ Client.cpp Solicitud.o SocketDatagrama.o PaqueteDatagrama.o -o Client
Solicitud.o: ../Libraries/Solicitud.cpp SocketDatagrama.o ../Libraries/Solicitud.h
	g++ ../Libraries/Solicitud.cpp -c
SocketDatagrama.o: ../Libraries/SocketDatagrama.cpp PaqueteDatagrama.o ../Libraries/SocketDatagrama.h
	g++ ../Libraries/SocketDatagrama.cpp -c
PaqueteDatagrama.o: ../Libraries/PaqueteDatagrama.cpp ../Libraries/PaqueteDatagrama.h
	g++ ../Libraries/PaqueteDatagrama.cpp -c
