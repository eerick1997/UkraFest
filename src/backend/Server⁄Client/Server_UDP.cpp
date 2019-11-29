#include "../Libraries/Respuesta.h"
#include <iostream>

using namespace std;

const char *name_image = "screen_shoot.png";

int main() {
    char *IP;
    string ip;
    int packet[ TAM_MAX_ARG ];
    char command[ TAM_MAX_ARG ];
    struct mensaje *request;
    cout << "IP: ";
    cin >> ip;
    cout << endl;
    IP = new char[ ip.length() ];
    strcpy( IP, ip.c_str() );
    Respuesta server( 7200, IP );
    while( true ) {
        request = server.getRequest();
        if( request != NULL ) {
            vector< int > bytes;
            memcpy( command, request -> arguments, sizeof( command ) );
            cout << command << endl;
            system( command );
            ifstream in( name_image, ios::binary );

            if( in.is_open() )
                while( !in.eof() )
                    bytes.push_back( in.get() );
            int number_packets = ceil( ( ( float )bytes.size() / (float)TAM_MAX_ARG ) );
            server.sendReply( (char *)&number_packets, number_packets );
            for( int npacket = 0, index = 0; npacket < number_packets; npacket++ ){
                cout << endl << npacket << endl << endl;
                for( int i = 0; i < TAM_MAX_ARG; i++ ){
                    packet[ i ] = bytes[ index ];
                    index++;
                    if( index == bytes.size() )
                        break;
                }
                server.sendReply( (char *)packet, npacket );
            }
            remove( name_image );
            in.close();
        }
    }
    return 0;
}