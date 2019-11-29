#include <map>

#ifndef __NODE__
#define __NODE__

class Node{
    public:
        bool isWord;
        std::map< char, Node* > letters;
        Node( );
};

#endif