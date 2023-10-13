#ifndef _HEAP_H
#define _HEAP_H

#include <vector>
#include <string>
#include "hash.h"

class heap {

public:

    // The constructor initializes the heap.
    heap(int capacity = 0);

    // Insert the goven string and key to the heap.
    int insert(const std::string &id, int key);
  
    // Change the key of an existing entry.
    int setKey(const std::string &id, int key);
  
    // Remove item from heap.
    int remove(std::string &id, int *key);
  
    // Remove top item from heap
    int deleteMin(std::string *id, int *key);
    
    // For testing purposes
    int test();

 
private:
 
    class node { // An inner class within heap
    public:
        std::string id; // The id of this node
        int key; // The key of this node
        void *pData; // A pointer to the actual data
        bool operator<(node n2) const { return key < n2.key; }
    };
 
    int filled = 0;
    int capacity = 0;
    std::vector<node> data; // The actual binary heap
    hashTable mapping; // maps ids to node pointers

    // Move a key higher up in the tree, to its correct location.
    int percUp(int posCur);
  
    // Move a key down the tree, to its correct location
    int percDown(int posCur);
    
    // Get position of given node (needs clarification)
    int getPos(node *pn);

};

#endif //_HEAP_H