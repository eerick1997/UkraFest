#include <bits/stdc++.h>
using namespace std;

int main(){

    ifstream inFile;
    string str1, str2, str3, str4;

    inFile.open("Words.txt");

    if(!inFile){
        cout << "No se ha encontrado el diccionario\n";
        exit(1);
    }

    
    while( inFile >> str1 >> str2 >> str3 >> str4 ){
        // cout << str2 << endl; No habilitar este comentario, son muchas palabras Xd
        // Ingresar las palabras a la clase Trie
    }

    inFile.close();

    return 0;
}