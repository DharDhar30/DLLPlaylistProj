#include "DNode.h"
#include "DLL.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

// Constructor - initializes an empty list
DLL::DLL(){
    last = nullptr;
    first = nullptr;
    numSongs = 0;
}

// Constructor - initializes a list with one new node
DLL::DLL(string t, string l, int m, int s){
    DNode *n = new DNode(t, l, m, s);
    first = n;
    last = n;
    numSongs = 1;
}

// Step 1: Push method - adds a new node to the end of the list
void DLL::push(string n, string a, int m, int s) {
    DNode *newNode = new DNode(n, a, m, s);
    if (first == nullptr) {
        first = newNode;
        last = newNode;
    } else {
        last->next = newNode;
        newNode->prev = last;
        last = newNode;
    }
    numSongs++;
}

// Step 2: Print list method - displays all songs using friend class access
void DLL::printList() {
    DNode *current = first;
    while (current != nullptr) {
        if (current->song != nullptr) {
            cout << current->song->title << ", "
                 << current->song->artist << "................"
                 << current->song->min << ":";

            int s = current->song->sec;
            if (s < 10) {
                cout << "0";
            }
            cout << s << endl;
        }
        current = current->next;
    }
}

// Step 3: Pop method - removes the last node and returns its song (O(1) time)
Song *DLL::pop() {
    if (first == nullptr) {
        return nullptr;
    }

    Song *removedSong = last->song;

    if (first == last) {
        delete last;
        first = nullptr;
        last = nullptr;
    } else {
        DNode *temp = last;
        last = last->prev;
        last->next = nullptr;
        delete temp;
    }

    numSongs--;
    return removedSong;
}

// Step 4: Remove method - finds a song by title and removes its node
int DLL::remove(string s) {
    DNode *current = first;
    int index = 0;

    while (current != nullptr) {
        if (current->song != nullptr && current->song->title == s) {
            cout << "Removing: " << current->song->title << ", "
                 << current->song->artist << " ................"
                 << current->song->min << ":"
                 << (current->song->sec < 10 ? "0" : "") << current->song->sec << endl;

            if (current == first && current == last) {
                first = nullptr;
                last = nullptr;
            } else if (current == first) {
                first = first->next;
                first->prev = nullptr;
            } else if (current == last) {
                last = last->prev;
                last->next = nullptr;
            } else {
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
    return -1; // Not found
}

// Step 5: Move Up method - moves song up one place, or wraps to the end if first
void DLL::moveUp(string s) {
    if (numSongs <= 1) return;

    DNode *current = first;
    while (current != nullptr && current->song->title != s) {
        current = current->next;
    }

    if (current == nullptr) return; // Not found

    if (current == first) {
        // Move first node to the end
        DNode *temp = first;
        first = first->next;
        first->prev = nullptr;

        last->next = temp;
        temp->prev = last;
        temp->next = nullptr;
        last = temp;
    } else {
        // Swap song data with the previous node
        Song *tempSong = current->song;
        current->song = current->prev->song;
        current->prev->song = tempSong;
    }
}

// Step 6: Move Down method - moves song down one place, or wraps to the front if last
void DLL::moveDown(string s) {
    if (numSongs <= 1) return;

    DNode *current = first;
    while (current != nullptr && current->song->title != s) {
        current = current->next;
    }

    if (current == nullptr) return; // Not found

    if (current == last) {
        // Move last node to the front
        DNode *temp = last;
        last = last->prev;
        last->next = nullptr;

        temp->next = first;
        first->prev = temp;
        temp->prev = nullptr;
        first = temp;
    } else {
        // Swap song data with the next node
        Song *tempSong = current->song;
        current->song = current->next->song;
        current->next->song = tempSong;
    }
}

// Step 7: List Duration method - sums up minutes and seconds via pointers
void DLL::listDuration(int *tm, int *ts) {
    *tm = 0;
    *ts = 0;
    DNode *current = first;
    while (current != nullptr) {
        if (current->song != nullptr) {
            *tm += current->song->min;
            *ts += current->song->sec;
        }
        current = current->next;
    }
}

// Step 8: Make Random method - randomly shuffles the playlist order
void DLL::makeRandom() {
    if (numSongs <= 1) return;

    vector<Song*> songVec;
    DNode *current = first;
    while (current != nullptr) {
        songVec.push_back(current->song);
        current = current->next;
    }

    // Shuffle vector elements
    for (int i = songVec.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        Song *temp = songVec[i];
        songVec[i] = songVec[j];
        songVec[j] = temp;
    }

    // Assign shuffled songs back into the nodes
    current = first;
    int idx = 0;
    while (current != nullptr) {
        current->song = songVec[idx++];
        current = current->next;
    }
}

// Step 9: Destructor (5 pts Extra Credit) - clears all nodes from heap
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