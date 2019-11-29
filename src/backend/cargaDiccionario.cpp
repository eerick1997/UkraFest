#include <bits/stdc++.h>
#include "../Libraries/Trie.h"

using namespace std;

int main(){

    ifstream inFile;
    string str1, str2, str3, str4;
    Trie trie;

    inFile.open("diccionario.txt"); // Cambiar el archivo de texto a Words.txt

    if(!inFile){
        cout << "No se ha encontrado el diccionario\n";
        exit(1);
    }
    
    while( inFile >> str1 >> str2 >> str3 >> str4 ){
        //cout << str2 << endl; //No habilitar este comentario, son muchas palabras Xd
        // Ingresar las palabras a la clase Trie
        trie.insert_word(str2);
    }
    inFile.close();

    return 0;
}