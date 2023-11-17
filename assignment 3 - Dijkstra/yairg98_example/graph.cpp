#include "graph.h"
using namespace std;


// Build the graph from the given file
void graph::load(string infile) {
	
	string line, v1, v2;
	int weight;
	vertex *pv;
	ifstream input(infile);
	
	// Record each graph edge line-by-line
	while ( getline(input, line) ) {
		// Parse the line, identifying v1, v2, and weight of edge
		stringstream ss(line);
		ss >> v1 >> v2 >> weight;
		edge e = edge(v1, v2, weight);
		
		// If v1 hasn't been seen yet, create a vertex and record pointer pv
		if ( ! vertices.contains(v1) ) {
			pv = (vertex *)(new vertex(v1));
			vertices.insert(v1, pv);
			seen.push_back(v1);
			size++;
		}
		
		// Otherwise, retrieve pointer to vertex v1
		else { pv = ((vertex *)vertices.getPointer(v1)); }
		
		// Add edge e to v1's adjacency list
		pv->adj.push_back(e);
		
		// Create vertex v2 and add it to "seen" list, if it doesn't exist already
		if ( ! vertices.contains(v2) ) {
			pv = (vertex *)(new vertex(v2));
			vertices.insert(v2, pv);
			seen.push_back(v2);
			size++;
		}
	}
}


// Check the validity of given vertex
bool graph::checkVertex(string v) {
	return vertices.contains(v);
}


// Run Dijkstra's algorithm to find the shortest path to each vertex
void graph::dijkstra(string start) {

	vertex *pv, *pv1, *pv2;
	
	// Retrieve the starting vertex pointer
	pv = (vertex *) vertices.getPointer(start);
	pv->dist = 0;
	pv->known = true;
	pv->path = start;

	// Add each edge leaving the start-vertex to the frontier
	heap frontier = heap(size);
	list<edge> :: iterator it;
	for ( it = pv->adj.begin(); it != pv->adj.end(); it++ ) {
		
		// Try to insert vertex to frontier
		if ( frontier.insert(it->v2, it->weight) == 0 ) {
			pv2 = (vertex *) vertices.getPointer(it->v2);
			pv2->dist = it->weight;
			pv2->path = (pv->path) + ", " + it->v2;
		}
		
		// If vertex is already in frontier, compare/change dist and path
		else {
			pv2 = (vertex *) vertices.getPointer(it->v2);
			if (it->weight < pv2->dist) {
				pv2->dist = it->weight;
				pv2->path = (pv->path) + ", " + it->v2;
			}
			frontier.setKey(it->v2, pv2->dist);
		}        
	}
	
	string id; // ID of the most vertex returned by deleteMin
	int dist; // shortest known distance to that vertex
	int w; // Net distance to new frontier vertex
	
	while ( !frontier.deleteMin(&id, &dist) ) {
		pv = (vertex *) vertices.getPointer(id);
		pv->known = true;
		
		// Expand frontier to include adjacent edges to current vertex
		for ( it = pv->adj.begin(); it != pv->adj.end(); it++ ) {
			
			// Check if new vertex is already known
			pv1 = (vertex *) vertices.getPointer(it->v1);
			pv2 = (vertex *) vertices.getPointer(it->v2);
			if ( pv2->known == true ) {
				continue;
			}
			
			// Frontier vertex dist = dist up to previous vertex + edge weight
			w = dist + it->weight;
			
			// Try to insert to frontier
			if ( frontier.insert(it->v2, w) == 0 ) {
				pv2 = (vertex *) vertices.getPointer(it->v2);
				pv2->dist = w;
				pv2->path = (pv1->path) + ", " + it->v2;
			}
			
			// If vertex is already in frontier, compare/change dist and path
			else {
				pv2 = (vertex *) vertices.getPointer(it->v2);
				if (w < pv2->dist) {
					pv2->dist = w;
					pv2->path = (pv1->path) + ", " + it->v2;
				}
				frontier.setKey(it->v2, pv2->dist);
			}
		}
	}
}


// Iterate through vertices in order and print shortest paths
void graph::show(string outfile) {
	
	vertex *pv;
	list<string> :: iterator it;
	ofstream output(outfile);
	
	// Print each vertex and its shortest path to the output file
	for ( it = seen.begin(); it != seen.end(); it++ ) {
		pv = (vertex *) vertices.getPointer(*it);
		// If no path was found...
		if (pv->dist == -1) {
			output << pv->id << ": NO PATH" << endl;
		}
		// If a path was found...
		else {
			output << pv->id << ": " << pv->dist << " [" << pv->path << "]" << endl;
		}
	}
}
    