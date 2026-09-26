#include "DNode.h"
#include "DLL.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

// Constructor - initializes an empty list
DLL::DLL() {
    last = nullptr;
    first = nullptr;
    numSongs = 0;
}

DLL::DLL(string t, string l, int m, int s) {
    DNode *n = new DNode(t, l, m, s);
    first = n;
    last = n;
    numSongs = 1;
}

void DLL::push(string n, string a, int m, int s) {
    DNode *newNode = new DNode(n, a, m, s);

    if (first == nullptr) {
        first = newNode;
        last = newNode;
    }
    else {
        last->next = newNode;
        newNode->prev = last;
        last = newNode;
    }

    numSongs++;
}

// Print list method
void DLL::printList() {
    DNode *current = first;

    while (current != nullptr) {
        cout << current->song->title << ", "
             << current->song->artist << "................"
             << current->song->min << ":";

        if (current->song->sec < 10) {
            cout << "0";
        }

        cout << current->song->sec << endl;

        current = current->next;
    }
}

// Pop method - removes the last node
Song *DLL::pop() {
    if (last == nullptr) {
        return nullptr;
    }

    Song *removedSong = last->song;

    if (first == last) {
        delete last;
        first = nullptr;
        last = nullptr;
    }
    else {
        DNode *temp = last;
        last = last->prev;
        last->next = nullptr;
        delete temp;
    }

    numSongs--;

    return removedSong;
}

// Remove method
int DLL::remove(string s) {
    DNode *current = first;
    int index = 0;

    while (current != nullptr) {
        if (current->song->title == s) {

            cout << "Removing: "
                 << current->song->title << ", "
                 << current->song->artist << " ................"
                 << current->song->min << ":";

            if (current->song->sec < 10) {
                cout << "0";
            }

            cout << current->song->sec << endl;

            if (current == first && current == last) {
                first = nullptr;
                last = nullptr;
            }
            else if (current == first) {
                first = current->next;
                first->prev = nullptr;
            }
            else if (current == last) {
                last = current->prev;
                last->next = nullptr;
            }
            else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }

            delete current;
            numSongs--;

            return index;
        }

        current = current->next;
        index++;
    }

    return -1;
}

// Move Up method
void DLL::moveUp(string s) {
    if (numSongs <= 1) {
        return;
    }

    DNode *current = first;

    while (current != nullptr && current->song->title != s) {
        current = current->next;
    }

    if (current == nullptr) {
        return;
    }

    if (current == first) {
        DNode *temp = first;

        first = first->next;
        first->prev = nullptr;

        last->next = temp;
        temp->prev = last;
        temp->next = nullptr;

        last = temp;
    }
    else {
        Song *tempSong = current->song;
        current->song = current->prev->song;
        current->prev->song = tempSong;
    }
}

// Move Down method
void DLL::moveDown(string s) {
    if (numSongs <= 1) {
        return;
    }

    DNode *current = first;

    while (current != nullptr && current->song->title != s) {
        current = current->next;
    }

    if (current == nullptr) {
        return;
    }

    if (current == last) {
        DNode *temp = last;

        last = last->prev;
        last->next = nullptr;

        temp->next = first;
        first->prev = temp;
        temp->prev = nullptr;

        first = temp;
    }
    else {
        Song *tempSong = current->song;
        current->song = current->next->song;
        current->next->song = tempSong;
    }
}

// List Duration method
void DLL::listDuration(int *tm, int *ts) {
    *tm = 0;
    *ts = 0;

    DNode *current = first;

    while (current != nullptr) {
        *tm += current->song->min;
        *ts += current->song->sec;

        current = current->next;
    }
}

// Make Random method
void DLL::makeRandom() {
    if (numSongs <= 1) {
        return;
    }

    vector<Song*> songVec;

    DNode *current = first;

    while (current != nullptr) {
        songVec.push_back(current->song);
        current = current->next;
    }

    for (int i = songVec.size() - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        Song *temp = songVec[i];
        songVec[i] = songVec[j];
        songVec[j] = temp;
    }

    current = first;
    int index = 0;

    while (current != nullptr) {
        current->song = songVec[index];
        current = current->next;
        index++;
    }
}

// Destructor
DLL::~DLL() {
    DNode *current = first;

    while (current != nullptr) {
        DNode *nextNode = current->next;
        delete current;
        current = nextNode;
    }

    first = nullptr;
    last = nullptr;
    numSongs = 0;
}