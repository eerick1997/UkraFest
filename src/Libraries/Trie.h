
#include "Node.h"

#ifndef __TRIE__
#define __TRIE__

class Trie {

    private:
        Node *root;

    public:
        Trie( );
        bool exists( Node *, const char & );
        void insert_word( const std::string & );
        bool find_word( const std::string & );
        void read_file( std::string );
};

#endif