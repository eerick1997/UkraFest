Server_UDP: Server_UDP.cpp Respuesta.o Trie.o Node.o SocketDatagrama.o PaqueteDatagrama.o
	g++ Server_UDP.cpp Respuesta.o SocketDatagrama.o PaqueteDatagrama.o Trie.o Node.o -o Server_UDP
Respuesta.o: ../../Libraries/Respuesta.cpp SocketDatagrama.o ../../Libraries/Respuesta.h
	g++ ../../Libraries/Respuesta.cpp -c
SocketDatagrama.o: ../../Libraries/SocketDatagrama.cpp PaqueteDatagrama.o ../../Libraries/SocketDatagrama.h
	g++ ../../Libraries/SocketDatagrama.cpp -c
PaqueteDatagrama.o: ../../Libraries/PaqueteDatagrama.cpp ../../Libraries/PaqueteDatagrama.h
	g++ ../../Libraries/PaqueteDatagrama.cpp -c
Trie.o: ../../Libraries/Trie.cpp ../../Libraries/Trie.h Node.o
	g++ ../../Libraries/Trie.cpp Node.o -c
Node.o: ../../Libraries/Node.cpp ../../Libraries/Node.h
	g++ ../../Libraries/Node.cpp -c
