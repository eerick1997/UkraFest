#include "../Libraries/Respuesta.h"
#include <bits/stdc++.h>

using namespace std;

map< int, int[ TAM_MAX_ARG ] > buffer;

void buildFile( char *nme_image ){
    string str = string( nme_image );
    ofstream out( str + ".png", ios::binary);
    for( auto block : buffer ){
        for( int i = 0; i < TAM_MAX_ARG; i++ ){
            if( block.second[ i ] == -1 )
                break;
            out.put( block.second[ i ] );
        }
    }
    out.close();
} 

int main() {
    Respuesta server( 7200 );
    struct mensaje *request;
    int info[ TAM_MAX_ARG ];
    
    int flag = 1;
    while (1){  
        request = server.getRequest();
        if( request != NULL ){
    
            memcpy( info, request -> arguments, sizeof( info ) );
            for( int i = 0; i < TAM_MAX_ARG; i++ )
                buffer[ request -> requestId ][ i ] = info[ i ];

            if( flag == request -> operationId )
                buildFile( server.obtenerDireccion() );

            server.sendReply((char *)&flag, suma);
            flag++;

        } else 
            server.sendReply((char *)&flag, REPETIDO);
    }
    return 0;
}