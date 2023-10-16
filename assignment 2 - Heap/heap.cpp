//---IMPORTANT------//
//Daniel Kim -assignment 2 
//I have gotten nontrivial help from Taseen Jahan
//Where I have gotten help is marked with comment

//a constructor that accepts an integer representing the capacity of the binary heap; 
//a public member function, insert, used to insert a new item into the heap; a public member function
//deleteMin, that removes and returns the item with the lowest key from the heap; a public member function, 
//setKey, providing both increaseKey and decreaseKey functionality; and a public member function, 
//remove, that allows the programmer to delete an item with a specified id from the heap. 


//ALL PROGRAM O(logN)!

//a hash table in which each hash entry includes a pointer to the associated node 

//My heap class contains four private data members. 
//Two are simple integers representing the capacity and the current size of the heap. 
//The third is a vector of node objects containing the actual data of the heap; 
//each node contains a string id, an integer key, and a pointer to void that can point to anything. (I made "node" a private nested class within the heap class.) 
//The fourth private data member is a hash table. Since the heap constructor is provided with the maximum size of the heap
//you may construct the hash table to be large enough such that there is a small likelihood of a rehash
// but that is up to you (I'll discuss how to do that in class). 
//Note that since items get removed from the heap, but only lazily deleted from the hash table, it is still possible that a rehash of the hash table will be necessary.

#include "heap.h"
#include <iostream>
#include <string>
using namespace std;


//
// heap - The constructor allocates space for the nodes of the heap
// and the mapping (hash table) based on the specified capacity
//
//MAPPING = HASHTABLE
  heap::heap(int capacity):mapping(capacity*2){
        data.resize(capacity+1);
        heap::capacity = capacity;
        current_size = 0;
  }

  //
  // insert - Inserts a new node into the binary heap
  // Inserts a node with the specified id string, key,
  // and optionally a pointer.
  // While I am inserting the key, I am not seeing why it's used as of right now[erase comment if I do see it]
  //They key is used to
  // determine the final position of the new node.
  //
  // Returns:
  //   0 on success
  //   1 if the heap is already filled to capacity
  //   2 if a node with the given id already exists (but the heap
  //     is not filled to capacity)
  //
  int heap::insert(const std::string &id, int key, void *pv ){
    if (capacity == current_size){ 
        return 1;
    }
    else if (mapping.contains(id)==true && capacity != current_size){
        return 2;
    }else{
        int new_position = current_size +1; 
        data[new_position].id = id; 
        data[new_position].key = key;
        data[new_position].pData = pv;
        percolateUp(new_position);
        current_size = new_position; 
        new_position = 0;
        return 0;
    }
}

  //
  // setKey - set the key of the specified node to the specified value
  //
  // I have decided that the class should provide this member function
  // instead of two separate increaseKey and decreaseKey functions.
  //
  // Returns:
  //   0 on success
  //   1 if a node with the given id does not exist
  //
  int heap::setKey(const std::string &id, int key){
    // Get the node's position based on the 'id' using 'getPos'.
      int pos = getPos((node *)mapping.getPointer(id));
    if(mapping.contains(id) == false){ 
      return 1; 
    }
    else{ 
      data[pos].key = key; 
      percolateUp(pos); 
      percolateDown(pos); 
    }

  }

  //
  // deleteMin - return the data associated with the smallest key
  //             and delete that node from the binary heap
  //
  // If pId is supplied (i.e., it is not nullptr), write to that address
  // the id of the node being deleted. If pKey is supplied, write to
  // that address the key of the node being deleted. If ppData is
  // supplied, write to that address the associated void pointer.
  //
  // Returns:
  //   0 on success
  //   1 if the heap is empty
  //
  // Textbook fig 6.12 referenced
  int heap::deleteMin(std::string *pId, int *pKey, void *ppData){
    //error handling 
    if(current_size == 0){ 
        return 1;
    }

    //Since I am using a min-heap tree, I need to delete the highest node(first) and percolate down. 
    else{
        if (pId != nullptr) {
      * pId = data[1].id;
    }
    if (pKey != nullptr) {
      * pKey = data[1].key;
    }
    if (ppData != nullptr){
    *(static_cast<void **> (ppData)) = data[1].pData;
    }
    return 0; 
  }
  }

  //
  // remove - delete the node with the specified id from the binary heap
  //
  // If pKey is supplied, write to that address the key of the node being deleted. 
  // If ppData is supplied, write to that address the associated void pointer.
  //
  // Returns:
  //   0 on success
  //   1 if a node with the given id does not exist
  //
  int heap::remove(const std::string &id, int *pKey = nullptr, void *ppData = nullptr){
    //error handling 
    // Get the node's position based on the 'id' using 'getPos'.
    int pos = getPos((node *)mapping.getPointer(id));
    if (mapping.contains(id) == false){ 
      return 1; 
    }

    //pKey - ppData handling 
    if(pKey != nullptr){ *pKey = data[pos].key;} 
    if(ppData != nullptr){*(static_cast < void ** > (ppData)) = data[pos].pData;}
    
    //I have gotten nontrivial help from Taseen Jahan below : 
    //Delete 
    mapping.remove(data[pos].id); 
    data[pos] = data[(current_size-1)]; 
    int oldKey, newKey; 
    oldKey = data[pos].key; 
    newKey = data[current_size].key; 
    return 0;    
    }


///////------------Private functions----------//
///////------standard percs&getPos() given----//

//Percolate up function 
//I am using min heap tree
void heap::percolateUp(int posCur) {
  //Storing the new node information 
  data[0] = data[posCur]; //Since we're not going to be using the 0th

//while children smaller than the parent
  while(data[posCur].key < data[(posCur/2)].key){ 
    data[posCur] = data[(posCur/2)]; 

    //FIGURE OUT HASH.CPP SETPOINTER
    mapping.setPointer(data[posCur].id, &data[posCur]);    
  
    posCur /= 2;    
    //swap! 
  }

  data[posCur] = data[0]; 
  mapping.setPointer(data[posCur].id, &data[posCur]);
  data[0].key = -1; //This assumes no given key will be negative 
  data[0].id = ""; 
  data[0].pData = nullptr; 
}


void heap::percolateDown(int posCur){
  
  //Storing the new node information 
  data[0] = data[posCur]; //Since we're not going to be using the 0th

//while children smaller than the parent
  while(data[posCur].key > data[(posCur/2)].key){ 
    data[posCur] = data[(posCur/2)]; 
    mapping.setPointer(data[posCur].id, &data[posCur]);    
    posCur /= 2;    
    //swap! 
  }

  data[posCur] = data[0]; 
  mapping.setPointer(data[posCur].id, &data[posCur]);
  data[0].key = -1; //This assumes no given key will be negative 
  data[0].id = ""; 
  data[0].pData = nullptr; 

}

int heap::getPos(heap::node * pn) {
  int pos = pn - &data[0];
  return pos;
};


    