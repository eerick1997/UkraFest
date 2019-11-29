#include "Trie.h"

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