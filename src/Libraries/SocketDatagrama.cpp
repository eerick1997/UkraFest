#include "SocketDatagrama.h"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

SocketDatagrama::SocketDatagrama( int port ) {
    s = socket( AF_INET, SOCK_DGRAM, 0 );
    bzero( (char *)&direccionLocal, sizeof( direccionLocal ) );
    direccionLocal.sin_family = AF_INET;
    direccionLocal.sin_addr.s_addr = INADDR_ANY;
    direccionLocal.sin_port = htons( port );
    bind(s, (struct sockaddr *)&direccionLocal, sizeof( direccionLocal ) );
}

SocketDatagrama::SocketDatagrama( int port, const char *IP ) {
    s = socket( AF_INET, SOCK_DGRAM, 0 );
    bzero((char *)&direccionLocal, sizeof(direccionLocal));
    direccionLocal.sin_family = AF_INET;
    direccionLocal.sin_addr.s_addr = inet_addr( IP );
    direccionLocal.sin_port = htons( port );
    bind(s, (struct sockaddr *)&direccionLocal, sizeof( direccionLocal ) );
}

int SocketDatagrama::envia(PaqueteDatagrama &p) {
    direccionForanea.sin_family = AF_INET;
    direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
    direccionForanea.sin_port = htons(p.obtienePuerto());
    return sendto(s, (char *)p.obtieneDatos(), p.obtieneLongitud() * sizeof(char), 0, (struct sockaddr *)&direccionForanea, sizeof(direccionForanea));
}

int SocketDatagrama::recibe(PaqueteDatagrama &p) {
    bzero((char *)&direccionForanea, sizeof(direccionForanea));
    socklen_t direccionForaneaLen = sizeof(direccionForanea);
    int tam = recvfrom(s, (char *)p.obtieneDatos(), p.obtieneLongitud() * sizeof(char), 0, (struct sockaddr *)&direccionForanea, &direccionForaneaLen);
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(direccionForanea.sin_addr), ip, INET_ADDRSTRLEN);
    p.inicializaIp(ip);
    p.inicializaPuerto(ntohs(direccionForanea.sin_port));
    return tam;
}

int SocketDatagrama::recibeTimeout(PaqueteDatagrama &p, time_t segundos, suseconds_t microsegundos) {
    timeout.tv_sec = segundos;
    timeout.tv_usec = microsegundos;
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
    bzero((char *)&direccionForanea, sizeof(direccionForanea));
    socklen_t direccionForaneaLen = sizeof(direccionForanea);
    int n = recvfrom(s, (char *)p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *)&direccionForanea, &direccionForaneaLen);
    if ( n < 0 ){
        if ( errno == EWOULDBLOCK )
            fprintf(stderr, "Tiempo para recepción transcurrido\n"), n = -1;
        else
            fprintf(stderr, "Error en recvfrom\n");
    } 
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(direccionForanea.sin_addr), ip, INET_ADDRSTRLEN);
    p.inicializaIp( ip );
    p.inicializaPuerto( ntohs(direccionForanea.sin_port) );
    return n;
}

SocketDatagrama::~SocketDatagrama() {
    close( s );
}
