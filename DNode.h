#ifndef DNODE_H
#define DNODE_H

#include <stdlib.h>
#include "Song.h"
using namespace std;

class DNode {
    friend class DLL; // gives the DLL class access to the private fields
    Song *song;
    DNode *prev;
    DNode *next;
public:
    DNode();
    DNode(string s, string a, int lenmin, int lensec);
};

#endif