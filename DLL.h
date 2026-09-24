#include "DNode.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
class DLL {
    DNode *first;
    DNode *last;
    int numSongs;
public:
    DLL(); // constructor - initializes an empty list
    DLL(string t, string l, int m, int s);
    void push(string t, string a, int m, int s);
    Song *pop(); //does what you'd think
    int remove(string t);
    void makeRandom(); // randomizes the order of the list
    void moveUp(string t);
    void moveDown(string t);
    void listDuration(int *tm, int *ts);
    void printList();
    ~DLL(); // Destructor (5 pts extra credit)
};