#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector< string > words = { "aeiou", "AEIOU", "ÁÉÍÓÚ", ".-,+´" };
    vector< string > newWords;

    for( string word : words ){
        string newWord = "";

        for( char c : word ){
            if( isalpha( c ) )
                newWord += tolower( c );
            else {
                cout << c;
                switch ( c ) {
                case 'Á':
                    newWord += 'á';
                break;
                case 'É':
                    newWord += 'é';
                break;
                case 'Í':
                    newWord += 'í';
                break;
                case 'Ó':
                    newWord += 'ó';
                break;
                case 'Ú':
                    newWord += 'ú';
                break;
                case 'Ü':
                    newWord += 'Ü';
                break;
                case 'Ñ':
                    newWord += 'ñ';
                break;
                }
            }
            cout << endl;
        }
        if( newWord[ 0 ] != ' ' )
            newWords.push_back( newWord );
        newWord.clear();
    }
    for( string word : newWords )
        cout << word << endl;

    return 0;
}