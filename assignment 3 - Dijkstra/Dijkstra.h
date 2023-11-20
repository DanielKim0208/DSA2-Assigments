#include <fstream>
#include <sstream>
#include <list>
#include <iterator>
#include <iostream> 
#include <chrono>
#include <fstream>
#include "heap.h" 
#include "hash.h"

using namespace std; 

class graph {
    private: 

    class vertex;
    class edge;

    hashTable verticeTable; // Table of vertices the node is connected to 
    
    list<string> checked; //list of checked vertices so I don't double input the vertice
    int size = 0; //size of the graph
    
    //edge structure, holds start and end node
    //holds weight as int 
    //constructor that takes parameters and initializes the data member
   

    struct vertex {
        bool known = false;
        string id; 
        list<edge> adj; 
        int distance = -1;
        string path = ""; 
        vertex(string s) : id(s) {}
    };

     struct edge { 
        int weight;
        string startVertex;
        string endVertex;
        edge(string start, string end, int w) : startVertex(start), endVertex(end), weight(w) {}
    };

    list<vertex *> verticeList; //list of vertices in the graph

    public: 

    void buildGraph(string filename); 
    
    void insert(edge e);

    bool LocateVertex(string v, bool findneed);

    void dijkstraSetup (string source, heap& frontier);

    void dijkstraAlgorithm(heap& frontier);

    void dijkstra(string source); 

    void print(string outfile);

    int main();
};
