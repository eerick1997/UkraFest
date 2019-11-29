#include "../Libraries/Solicitud.h"
#include <bits/stdc++.h>
#include <time.h>

using namespace std;

void takeSS( int quality ){
    string command = "cd Images";
    system( command.c_str() );
    command = "scrot scroto.png -q " + to_string(quality);
    cout << command << endl;
    cout << command.c_str() << endl;
    system( command.c_str() );
}

int main(){
    takeSS( 10 );
    ifstream in( "scroto.png", ios::binary );
    int info[ TAM_MAX_ARG ], res = 0;
    vector< int > bytes;
    Solicitud sol;
    string IP; 
    int count = 0;
    cout << "Ingrese la IP: ";
    cin >> IP;
    char *ip = new char[IP.length()];
    strcpy(ip, IP.c_str());
    
    if( in.is_open() )
        while( !in.eof() )
            bytes.push_back( in.get() );
    
    for( int i = 0; i < bytes.size(); i += TAM_MAX_ARG ){
        for( int j = 0; (j < TAM_MAX_ARG) && (( i + j ) < bytes.size()); j++ )
            info[ j ] = bytes[ i + j ];
        char *resServer = sol.doOperation( ip, 7200, ceil( (float)bytes.size() / (float)TAM_MAX_ARG ), (char *)&info );
        memcpy( &res, resServer, sizeof( res ) );
    }
    in.close();
    remove("scroto.png");
    return 0;
}