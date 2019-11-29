#include "Respuesta.h"
#include <iostream>

using namespace std;

Respuesta::Respuesta( int port, const char *IP ){
    socketlocal = new SocketDatagrama( port, IP );
    clientePaqueteDatagrama = new PaqueteDatagrama( sizeof(mensaje) );
}

struct mensaje *Respuesta::getRequest(void){
    PaqueteDatagrama paq( sizeof(struct mensaje) );
    socketlocal -> recibe( paq );
    memcpy( clientePaqueteDatagrama, &paq, sizeof( paq ) );
    memcpy( &petition, clientePaqueteDatagrama -> obtieneDatos(), clientePaqueteDatagrama -> obtieneLongitud() );
    return &petition;
}

char *Respuesta::obtenerDireccion(){
    return clientePaqueteDatagrama -> obtieneDireccion();
}

void Respuesta::sendReply(char *respuesta, int type){
    struct mensaje response;
    memcpy( response.arguments, respuesta, TAM_MAX_ARG * sizeof( int ) );
    response.messageType = type;
    PaqueteDatagrama paqueteDatagrama( sizeof(struct mensaje) );
    paqueteDatagrama.inicializaDatos( (char *)&response );
    paqueteDatagrama.inicializaIp( clientePaqueteDatagrama -> obtieneDireccion() );
    paqueteDatagrama.inicializaPuerto( clientePaqueteDatagrama -> obtienePuerto() );
    socketlocal -> envia( paqueteDatagrama );
}
