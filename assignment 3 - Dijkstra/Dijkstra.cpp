//DANIEL KIM - ASSIGNMENT 3 FINAL

#include "Dijkstra.h"
using namespace std; 

//This 'main' function ask for the input file, output file, and starting vertex
//It then calls the buildGraph function to build the graph
//Then it calls the dijkstra function to find the shortest path
//Then it calls the print function to print the shortest path to the output file
//It also times how long it takes to run the program
int main() {

	// Declare variables
    string infile, outfile, start;
    graph g;

	// Prompt user for input file, output file, and starting vertex
    cout << "Enter the name of the input file: ";
    cin >> infile;
    cout << "Enter the name of the output file: ";
    cin >> outfile;
    cout << "Enter the starting vertex: ";
    cin >> start;

	// Build + sort graph and time how long it takes
	chrono::high_resolution_clock::time_point startTime = chrono::high_resolution_clock::now();
    g.buildGraph(infile);
    

    g.dijkstra(start);

    chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> timeTaken = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
    g.print(outfile);
    std::cout << std::fixed;
    std::cout << "Time taken: " << timeTaken.count() << " seconds" << std::endl;

    return 0;
}

//Reading and building the graph 
//This function takes in the input file and reads it line by line based on the given format
//It then inserts the edges into the graph
void graph::buildGraph(string filename){
    ifstream input(filename); 
    string line; 
    
    while(getline(input, line)){
        //Each line is made of source and destination nodes + edge weight
        //inputting as edges
        string start, end;
        int weight;
        stringstream ss(line); 
        ss >> start >> end >> weight;
        edge e = edge(start, end, weight);
        insert(e);
    }   
}

//This function takes in the edge and inserts it into the graph
void graph::insert(edge e){
    vertex *pv;

    if (!LocateVertex(e.startVertex, false)){
        pv = (vertex *)(new vertex(e.startVertex));
        verticeTable.insert(e.startVertex, pv);
        checked.push_back(e.startVertex);
        size++;
    }
    else{
        pv = ((vertex *)verticeTable.getPointer(e.startVertex));
    }
    pv->adj.push_back(e);

    if (!LocateVertex(e.endVertex, false)){
        pv = (vertex *)(new vertex(e.endVertex));
        verticeTable.insert(e.endVertex, pv);
        checked.push_back(e.endVertex);
        size++;
    }
};


//REFERENCE STRUCTURE FOR THE VERTEX
    //struct vertex {
        //string id; 
        //list<edge> adj; 
        //int distance = -1;
        //list<string> path; 
        //vertex(string s) : id(s) {}
    //};

// Combined dijkstra function
// Run Dijkstra's algorithm to find the shortest path to each vertex
// I have divided the dijkstra function into two parts for easier debug and readability
// I have referenced wwu source during implementation : 
// https://facultyweb.cs.wwu.edu/~wehrwes/courses/csci241_19w/lectures/L20/L20.pdf
// Taaseen helped me for this function
void graph::dijkstra(string source) {
    heap frontier = heap(size);
    dijkstraSetup(source, frontier);
    dijkstraAlgorithm(frontier);
}


//This function sets up the initial conditions for Dijkstra's algorithm 
//by initializing the source vertex and populating the frontier heap with its adjacent vertices.
void graph::dijkstraSetup(string source, heap& frontier) {

	//setting up the vertex pointers
    vertex *pv, *pv2;

	//set the source vertex to known, distance to 0, and path to itself
    pv = (vertex *) verticeTable.getPointer(source);
    pv->distance = 0;
    pv->known = true;
    pv->path = source;

	//Iterating over adjacent vertices and setting their distance and path
    for (const auto &it : pv->adj) {

		//Try to insert the vertex into the frontier heap
        if (frontier.insert(it.endVertex, it.weight) == 0) {

			//// If the insertion is successful, update the distance and path of the adjacent vertex
            pv2 = (vertex *) verticeTable.getPointer(it.endVertex);
            pv2->distance = it.weight;
            pv2->path = (pv->path) + ", " + it.endVertex;

			//If not successful, 
			//it means that vertex is already in the frontier 
			//compare distances and update if necessary
        } else {
            pv2 = (vertex *) verticeTable.getPointer(it.endVertex);
            if (it.weight < pv2->distance) {
                pv2->distance = it.weight;
                pv2->path = (pv->path) + ", " + it.endVertex;
            }
            frontier.setKey(it.endVertex, pv2->distance);
        }
    }
}


//using data setup by dijkstrasetup, 
//perform the main steps of Dijkstra's algorithm, 
//updating the distances and paths to vertices in the graph based on the information 
//obtained from the source vertex and its adjacent vertices.
void graph::dijkstraAlgorithm(heap& frontier) {
    // Variables to store vertex information during processing
    string id;
    int dist;
    int w;
    vertex *pv, *pv1, *pv2;

    // Main loop: continue until the frontier heap is empty
    while (!frontier.deleteMin(&id, &dist)) {
        // Retrieve the vertex pointer for the current vertex from the vertex table
        pv = (vertex *) verticeTable.getPointer(id);

        // Mark the current vertex as 'known' since it is being processed
        pv->known = true;

        // Iterate over the adjacent vertices of the current vertex
        for (const auto &it : pv->adj) {
            // Get pointers to the start and end vertices of the current edge
            pv1 = (vertex *) verticeTable.getPointer(it.startVertex);
            pv2 = (vertex *) verticeTable.getPointer(it.endVertex);

            // Skip if the end vertex is already known, as it has been processed
            if (pv2->known == true) {
                continue;
            }

            // Calculate the total distance to the end vertex through the current edge
            w = dist + it.weight;

            // Attempt to insert the end vertex into the frontier heap
            if (frontier.insert(it.endVertex, w) == 0) {
                // If insertion is successful, update distance and path of the end vertex
                pv2 = (vertex *) verticeTable.getPointer(it.endVertex);
                pv2->distance = w;
                pv2->path = (pv1->path) + ", " + it.endVertex;
            } else {
                // If the end vertex is already in the frontier, compare distances and update if necessary
                pv2 = (vertex *) verticeTable.getPointer(it.endVertex);
                if (w < pv2->distance) {
                    pv2->distance = w;
                    pv2->path = (pv1->path) + ", " + it.endVertex;
                }
                // Adjust the key (distance) of the end vertex in the frontier heap
                frontier.setKey(it.endVertex, pv2->distance);
            }
        }
    }
}







// Iterate through vertices in order and print shortest paths
//Taaseen helped me for this function 
void graph::print(string outfile) {
	
	vertex *pv;
	list<string> :: iterator it;
	ofstream output(outfile);
	
	// Print each vertex and its shortest path to the output file
	for ( it = checked.begin(); it != checked.end(); it++ ) {
		pv = (vertex *) verticeTable.getPointer(*it);
		// If no path was found...
		if (pv->distance == -1) {
			output << pv->id << ": NO PATH" << endl;
		}
		// If a path was found...
		else {
			output << pv->id << ": " << pv->distance << " [" << pv->path << "]" << endl;
		}
	}
}

//I thought I might have to locate the vertex in the graph, but I didn't
//ALL call to this funcion assume findneed = false
bool graph::LocateVertex(string v, bool findneed){
    if (findneed == false){ 
        return verticeTable.contains(v);
    }
};










