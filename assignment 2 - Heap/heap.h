//Header file for heaps, defining public and private functions

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

 
private:

    

 
    class node { // An inner class within heap
    public:
        std::string id; // The id of this node
        int key; // The key of this node
        void *pData; // A pointer to the actual data
    };

    int capacity;
    int size;
    std::vector<node> data; // The actual binary heap
    hashTable mapping; // maps ids to node pointers

    void percolateUp(int posCur);

    void percolateDown(int posCur);

    int getPos(node *pn);
    
};

#endif