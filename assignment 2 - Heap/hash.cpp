//DANIEL KIM - FINAL.VER
#include "hash.h"
#include <iostream>
using namespace std;


hashTable::hashTable(int size){
		capacity = getPrime(size);
		data.resize(capacity);
		filled = 0;
	}

// Insert the specified key into the hash table.
  // If an optional pointer is provided,
  // associate that pointer with the key.
  // Returns 0 on success,
  // 1 if key already exists in hash table,
  // 2 if rehash fails.

//Using the already provided hashItem by the hash.cpp, 
int hashTable::insert(const std::string &key, void *pv){ 
int pos = hash(key); 

// Search for the location of a key in the data structure
while (true) {
    // Check if the current position is occupied and if its key is equal to the target key
    if (!data[pos].isOccupied || data[pos].key == key) {
        break;  // Exit the loop if the key is found or an unoccupied spot is encountered
    }

    // If the current position is occupied and doesn't match the key, move to the next position
    pos = (pos + 1) % capacity;
}

// At this point, either the key has been found or an unoccupied spot has been reached
if (data[pos].isOccupied && data[pos].key == key) {
    // Key found at position 'pos'
    return 1;
} else if((filled/capacity)>0.5){ 
    if (rehash()==false){
        return 2;
    }
}

data[pos].key = key; 
data[pos].isOccupied = true; 
data[pos].isDeleted = false;
filled++;
return 0;
}


  // Check if the specified key is in the hash table.
  // If so, return true; otherwise, return false.
bool hashTable::contains(const std::string &key){
    int containCheck = findPos(key);
    if (containCheck != -1){
        return true;
    }else{
        return false;
    }
}

//--------------------ADDED FOR 2ND ASSIGNMENT--------------------------------------------///

  // Get the pointer associated with the specified key.
  // If the key does not exist in the hash table, return nullptr.
  // If an optional pointer to a bool is provided,
  // set the bool to true if the key is in the hash table,
  // and set the bool to false otherwise.
void *hashTable::getPointer(const std::string &key, bool *b)
{
    int pos = findPos(key);

    if (b != nullptr) {
        *b = (pos != -1);
    }

    if (pos == -1) {
        return nullptr;
    }

    else {
        return data[pos].pv;
    }
}


  // Set the pointer associated with the specified key.
  // Returns 0 on success,
  // 1 if the key does not exist in the hash table.
  int hashTable::setPointer(const std::string & key, void * pv) {
  if (contains(key) == false) {
    return 1;
  } else {
    data[findPos(key)].pv = pv;
    return 0;
  }
};

  // Delete the item with the specified key.
  // Returns true on success,
  // false if the specified key is not in the hash table.
bool hashTable::remove(const std::string &key)
{
    int pos = findPos(key);
    if (pos != -1)
    {
        data[pos].isDeleted = true;
        return true;
    }
    return false;
}


//--------------------END OF ADDED FOR 2ND ASSIGNMENT---------------------------------------///


//borrowed from textbook fig 5.4 
int hashTable::hash(const string &key){
    unsigned int hashVal = 0;

    for(char ch: key){ 
        hashVal = 37 * hashVal + ch; 
    }
    return hashVal % capacity;  
}


//Linear probing to find the position 
int hashTable::findPos(const std::string &key){ 

    //get the initial position by hashing the key 
    int pos = hash(key); 

    //if the position is occupied, enter the linear probe loop
    //cell key already in use, go to the next one until find the match
    //If reach the end, start from the beginning 
    //If can't find  
    while (data[pos].isOccupied){
        if(data[pos].key == key){
            return pos;
        }
        ++pos;
        if(pos == capacity){ 
            pos = 0;
        }
    }
    return -1; 
}

//borrowed from textbook fig 5.22, but modified a little
//(Textbook example was on the quadratic probing)
bool hashTable:: rehash(){ 

    int newSize = getPrime(capacity);
    vector<hashItem>olddata;
    data.swap(olddata);
    
    try{data.resize(newSize);} 
    catch (std::bad_alloc){
        return false;
    }
    capacity =  newSize; 
    filled = 0; 

    for (auto & item : olddata){
        if((item.isOccupied == true)){ 
            insert(item.key);
        } 
        return true;
    }    
}

//give prime numbers based on the input table size
unsigned int hashTable::getPrime(int size) {
  unsigned int primesize = size;
  static int primeNo[] = {98317, 196613, 393241, 786433, 1572869, 3145739};
   for (int i : primeNo) {
        if (i > size) {
            return i;
        }
    }
    // If dictionary is oversized, print an error message
    std::cout << "ERROR: dictionary oversized" << std::endl;
    return 3145739;
};

