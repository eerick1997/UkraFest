#include "../../Libraries/Respuesta.h"
#include "../../Libraries/Trie.h"
#include <bits/stdc++.h>

using namespace std;

string name_file = "my_piece_of_file";
int RECEIVED[ 1 ] = { -1 };

int main() {
    int64_t count_words;
    Trie trie;
    trie.read_file( "../Words.txt" );
    ofstream out_file( name_file, ios::binary );
    char *IP;
    string ip;
    struct mensaje *request;
    cout << "IP: ";
    cin >> ip;
    cout << endl;
    IP = new char[ ip.length() ];
    strcpy( IP, ip.c_str() );
    vector< int > bytes;
    Respuesta server( 7200, IP );
    while( true ) {
        count_words = 0;
        char buffer[ TAM_MAX_ARG ];
        request = server.getRequest();
        if( request != NULL ) {
            cout << "Non null" << endl;
            memcpy( buffer, request -> arguments, sizeof( buffer ) );

            for( int n_byte = 0; n_byte < TAM_MAX_ARG; n_byte++ ){
                cout << buffer[ n_byte ] << " ";
                if( buffer[ n_byte ] != -1 )
                    bytes.push_back( buffer[ n_byte ] );
                else {
                    out_file.close();
                    ifstream in_file;
                    in_file.open( name_file );
                    string word;
                    while( in_file >> word ){
                        if( trie.find_word( word ) )
                            count_words++;
                    }
                    RECEIVED[ 0 ] = count_words;
                }
            }

            if( RECEIVED[ 0 ] < 0 ){
            for( int byte : bytes )
                out_file.put( byte );
            }

            server.sendReply( (char *)RECEIVED, 1 );
        } else {
            cout << "is null " << endl;
        }
    }
    return 0;
}