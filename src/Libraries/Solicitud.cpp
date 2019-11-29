#include "Solicitud.h"
#include <sys/time.h>
#include <vector>
#include <iostream>

using namespace std;

int Solicitud::requestID = 0;

Solicitud::Solicitud() {
    socketlocal = new SocketDatagrama( 0 );
}

char * Solicitud::doOperation( char *IP, int puerto, int operationId, char *arguments ) {
    int n = 7;
    int packets = 2;
    time_t segundos = 2;
    suseconds_t microsegundos = 500000;
    char respuesta[TAM_MAX_DATA];

    struct mensaje datos;
    datos.messageType = 1123456;
    datos.requestId = requestID;
    datos.operationId = operationId;
     cout<<"hola"<<endl;
    memcpy(datos.arguments, arguments, TAM_MAX_DATA * sizeof( char ) );

    PaqueteDatagrama paq( (char *)&datos, sizeof( struct mensaje ), IP, puerto );
    PaqueteDatagrama paq2( sizeof( struct mensaje ) );

    int result = -1;
    while ( (n--) > 0 && result == -1 ) {
        socketlocal -> envia( paq );
        result = socketlocal -> recibeTimeout( paq2, segundos, microsegundos );
    }
    if ( result == -1 ) {
        printf("Servidor no disponible\n");
        return {};
    }else{

    }
    memcpy( &response, paq2.obtieneDatos(), sizeof( struct mensaje ) );
   // memcpy( &packets, response.arguments, sizeof( int ) );

    return response.arguments;
}