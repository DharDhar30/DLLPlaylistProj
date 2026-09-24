#include "DNode.h"
#include <string>

using namespace std;

DNode::DNode() {
    song = nullptr;
    prev = nullptr;
    next = nullptr;
}

DNode::DNode(string s, string a, int lenmin, int lensec) {
    song = new Song(s, a, lenmin, lensec);
    prev = nullptr;
    next = nullptr;
}