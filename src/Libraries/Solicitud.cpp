#include "Solicitud.h"
#include <sys/time.h>
#include <vector>
#include <iostream>

using namespace std;

int Solicitud::requestID = 0;

Solicitud::Solicitud() {
    socketlocal = new SocketDatagrama( 0 );
}

vector< int > Solicitud::doOperation( char *IP, int puerto, int operationId, char *arguments ) {
    int n = 7;
    int packets = 0;
    time_t segundos = 2;
    suseconds_t microsegundos = 500000;
    vector< int > image;

    struct mensaje datos;
    datos.messageType = 1123456;
    datos.requestId = requestID;
    datos.operationId = operationId;
    
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
    }
    memcpy( &response, paq2.obtieneDatos(), sizeof( struct mensaje ) );
    memcpy( &packets, response.arguments, sizeof( int ) );
    cout << packets << endl;
    int packet[ TAM_MAX_ARG ];

    for( int i = 0; i < packets; i++ ){
        socketlocal -> recibeTimeout( paq2, segundos, microsegundos );
        memcpy( &response, paq2.obtieneDatos(), sizeof( struct mensaje ) );
        memcpy( packet, response.arguments, TAM_MAX_ARG * sizeof( int ) );
        
        cout << endl << i << " #" << response.messageType << endl << endl;
        for( int byte = 0; byte < TAM_MAX_ARG; byte++ ){
            
            //cout << packet[ byte ] << " ";
            if( packet[ byte ] != -1 )
                image.push_back( packet[ byte ] );
            else 
                break;
            
        }
        cout << endl;
    }
    return image;
}