//---IMPORTANT------//
//Daniel Kim -assignment 2 
//I have gotten nontrivial help from Taseen Jahan
//Where I have gotten help is marked with comment
//I have used chatGPT and github copilot for help ; locations marked
//I have also used the textbook for help; locations marked
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
  // While I am inserting the pointer, I am not seeing why it's used as of right now[erase comment if I do see it]
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
    if (capacity <= current_size){ return 1;}
    else if (mapping.contains(id)==true && capacity != current_size){return 2;}
    else{
        int new_position = current_size +1; 
        data[new_position].id = id; 
        data[new_position].key = key;
        //handling *pv(useheap retval line 61 does not use pointer)
        if(pv == nullptr){data[new_position].pData = nullptr;}
        else{data[new_position].pData = pv;}
        data[new_position].pData = pv;
        mapping.insert(data[new_position].id, &data[new_position]);
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
    bool b;
    int pos = getPos((node *)mapping.getPointer(id, & b));
    if(b == false){ return 1;}
    else{ 
      data[pos].key = key; 
      percolateUp(pos); 
      percolateDown(pos); 
      return 0;
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
int heap::deleteMin(std::string *pId, int *pKey, void *ppData) {
  if (current_size == 0) {return 1;}
  if (pId != nullptr) {*pId = data[1].id;}
  if (pKey != nullptr) {*pKey = data[1].key;}
  if (ppData != nullptr) {*reinterpret_cast<void**>(ppData) = data[1].pData;}

  mapping.remove(data[1].id);
  data[1] = data[current_size];
  mapping.setPointer(data[1].id, &data[1]);
  mapping.remove(data[current_size].id);
  current_size--;
  percolateDown(1);
  return 0;
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
  int heap::remove(const std::string &id, int *pKey, void *ppData){
    //error handling 
    // Get the node's position based on the 'id' using 'getPos'.
    bool b;
    int pos = getPos((node *)mapping.getPointer(id, & b));
    if (b == false){return 1;}

    //pKey - ppData handling 
    if(pKey != nullptr){ *pKey = data[pos].key;} 
    if(ppData != nullptr){*(reinterpret_cast < void ** > (ppData)) = data[pos].pData;}
    
    //I have gotten nontrivial help from Taseen Jahan below : 
    //Delete 
    mapping.remove(data[pos].id); 
    data[pos] = data[current_size];
    mapping.setPointer(data[pos].id, &data[pos]);
    data[current_size] = heap::node();
    if (data[current_size].key < data[pos].key) {percolateUp(pos);}
    else {percolateDown(pos);}
    return 0;
}


///////------------Private functions----------//
///////------standard percs&getPos() given----//


//Percolate up function 
//I am using min heap tree
void heap::percolateUp(int posCur) {

  while (data[posCur].key < data[posCur / 2].key && posCur > 1) {
    
    //using data[0] as temporary storage
    //swapping
    data[0] = data[posCur];
    data[posCur] = data[posCur / 2];
    data[posCur / 2] = data[0];

    mapping.setPointer(data[posCur].id, &data[posCur]);
    mapping.setPointer(data[posCur / 2].id, &data[posCur / 2]);
    posCur = posCur / 2;
  }

  //cleaning data[0]
  data[0].id = "";
  data[0].key = 0;
  data[0].pData = nullptr;
};


void heap::percolateDown(int posCur) {
    for (int pos = 2 * posCur; pos <= current_size; pos = 2 * pos) {
        if (pos <= current_size - 1 && data[pos].key > data[pos + 1].key) {
            pos++;
        }
        if (data[posCur].key > data[pos].key) {
            data[0] = data[posCur];
            data[posCur] = data[pos];
            data[pos] = data[0];
            mapping.setPointer(data[posCur].id, &data[posCur]);
            mapping.setPointer(data[pos].id, &data[pos]);
            posCur = pos;
        } else {
            break;
        }
    }
}


int heap::getPos(heap::node * pn) {
  int pos = pn - &data[0];
  return pos;
};
