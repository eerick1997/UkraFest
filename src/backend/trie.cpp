#include <bits/stdc++.h>

using namespace std;

struct Node{
    bool isWord = false;
    map< char, Node* > letters;
};

struct Trie{

    Node *root;

    Trie(){
        root = new Node();
    }

    inline bool exists( Node *actual, const char & c ){
        return actual -> letters.find( c ) != actual -> letters.end();
    }

    void insert_word( const string &word ){
        Node *current = root;
        for( auto & c : word ){
            if( !exists( current, c ) )
                current -> letters[ c ] = new Node();
            current = current -> letters[ c ];
        }
        current -> isWord = true;
    }

    bool find_word( const string &word ){
        Node *current = root;
        for( auto & c: word ){
            if( !exists( current, c ) )
                return false;
            current = current -> letters[ c ];
        }
        return current -> isWord;
    }

};

int main(){
    Trie trie;
    trie.insert_word("gato");
    trie.insert_word("gata");
    trie.insert_word("gat");

    cout << trie.find_word("gato") << endl;
    cout << trie.find_word("gata") << endl;
    cout << trie.find_word("gat") << endl;
    cout << trie.find_word("gate") << endl;

}