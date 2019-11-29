#include "../../Libraries/Respuesta.h"
#include "../../Libraries/Trie.h"
#include <bits/stdc++.h>

using namespace std;

string name_file = "my_piece_of_file";
int RECEIVED[ 1 ] = { -1 };

int main() {
    int64_t count_words;
    int response = -1;
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
    char buffer[ TAM_MAX_ARG ];
    while( true ) {
        count_words = 0;
        request = server.getRequest();
        if( request != NULL ) {
            cout << "Non null" << endl;
            memcpy( buffer, request -> arguments, sizeof( buffer ) );

            for( int n_byte = 0; n_byte < TAM_MAX_ARG; n_byte++ ){
                //cout << n_byte << endl;
                cout << buffer[ n_byte ] << " ";
                if( buffer[ n_byte ] != -1 )
                    bytes.push_back( buffer[ n_byte ] );
                else {
                    for( int c : bytes ){
                        out_file.put( c );
                    }
                        //cout << c << " ";
                    out_file.close();
                    ifstream in_file;
                    in_file.open( name_file );
                    string word;
                    while( in_file >> word ){
                        //cout << word << endl;
                        if( trie.find_word( word ) ){
                            cout << word << endl;
                            count_words++;
                        }
                    }
                    response = count_words;
                    cout << response << endl;
                    in_file.close();
                    break;
                }
            }

            server.sendReply( (char *)&response  );
        } else {
            cout << "is null " << endl;
        }
    }
    return 0;
}