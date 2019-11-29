#include "../../Libraries/Respuesta.h"
#include "../../Libraries/Trie.h"
#include <iostream>

using namespace std;

const char *name_image = "screen_shoot.png";

int main() {
    Trie trie;
    char *IP;
    string ip;
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
            char words[ 20000 ];
            memcpy( words, request -> arguments, sizeof( words ) );

            server.sendReply( (char *)words, 1 );
    }
    return 0;
}