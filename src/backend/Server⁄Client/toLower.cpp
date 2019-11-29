#include <string>
#include <iostream>
#include <vector>
#include<bits/stdc++.h>

using namespace std;

int main() {
    vector< string > words = { "aeiou", "AEIOU", "ÁÉÍÓÚ", "áéíóú", ".-,+´" };
    vector< string > newWords;

    string cad_aux = "áéíóú";

    for( string word : words ){

        string newWord = "";

        for(int i=0; i<word.length(); i++){

            if( isalpha(word[i]) )
                newWord += tolower(word[i]);

            else{

                int aux = (int)word[i];

                if( aux == -61 )
                    newWord += word[i];

                else if ( aux == -127 || aux == -95 )
                    newWord += cad_aux[1];

                else if( aux ==  -119 || aux == -87 )
                    newWord += cad_aux[3];

                else if( aux ==  -115 || aux == -83 )
                    newWord += cad_aux[5];

                else if( aux ==  -109 || aux == -77 )
                    newWord += cad_aux[7];

                else if( aux ==  -102 || aux == -70 )
                    newWord += cad_aux[9];

            }

        }

        if( newWord.length() != 0)
            newWords.push_back( newWord );
    }

    cout << endl << endl;
    for( string word : newWords )
        cout << word << endl;

    return 0;
}