#include "Trie.h"
#include <iostream>
#include <bits/stdc++.h>

Trie::Trie(){
    root = new Node();
}

bool Trie::exists( Node *actual, const char &c ) {
    return actual -> letters.find( c ) != actual -> letters.end();
}

void Trie::insert_word( const std::string &word ) {
    Node *current = root;
    for( auto & c : word ) {
        if( !exists( current, c ) )
            current -> letters[ c ] = new Node();
        current = current -> letters[ c ];
    }
    current -> isWord = true;
}

bool Trie::find_word( const std::string &word ) {
    Node *current = root;
    for( auto & c : word ) {
        if( !exists( current, c ) )
            return false;
        current = current -> letters[ c ];
    }
    return current -> isWord;
}

void Trie::read_file( std::string name_file ) {
    std::ifstream in_file;
    std::string str1, str2, str3, str4;
    in_file.open( name_file );
    if( !in_file ) {
        std::cout << "No se ha encontrado el diccionario " + name_file << endl;
        exit( -1 );
    }
    while( in_file >> str1 >> str2 >> str3 >> str4 )
        insert_word( str2 );

    in_file.close();
}