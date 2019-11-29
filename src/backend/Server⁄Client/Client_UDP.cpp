#include "../Libraries/Solicitud.h"
#include <sys/stat.h>
#include <vector>
#include <string>
#include <thread>

using namespace std;

const int port = 7200;
vector< string > IPrange; 


void get_ip_range( ) {
    
    IPrange.push_back("127.0.0.1");
    IPrange.push_back("10.100.77.143");
}

void send_request_ss( int quality, int time ) {
    Solicitud request;
    string Command = "scrot screen_shoot.png -q " + to_string( quality );
    for( auto IP: IPrange ) {
        char *ip = new char[ IP.length() ];
        char *command = new char[ Command.length() ];
        int32_t number_of_packets;
        strcpy( ip, IP.c_str() );
        strcpy( command, Command.c_str() );
        cout << ip << endl;
        cout << command << endl;
        vector< int  > image = request.doOperation( ip, port, 1, command );
        if( image.size() > 0 ){
            ofstream out( "Images/" + IP + ".png", ios::binary );
            for( auto byte : image )   
                out.put( byte );
            out.close();
        }
        this_thread::sleep_for( chrono::seconds( 1 ) );
    }
}

int main(){
    int quality, time;
    cin >> quality >> time;
    get_ip_range(  );
    mkdir( "Images", 0700 );
    while( true ){
        send_request_ss( quality, time );
        this_thread::sleep_for( chrono::seconds( abs( time - 1 ) ) );
    }
    
    return 0;
}