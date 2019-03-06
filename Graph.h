// Developer: Willie Gross
// Graph.h

// Purpose: defines a graph class for use in storing a vertex/edge graph

// NOTE: Compile with "g++ -std=c++11 ... "

// Function Libraries
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

#ifndef GRAPH_H
#define GRAPH_H
class Graph
{
	private:
		// suppressed constructors
		Graph(const Graph &rhs); 
		
		// private member functions/variables
		void DFS_helper(int vertex, bool visited[]);
		
		int **index_matrix; 		// 2-d integer array that will store the graph via its vertices
		queue<int> adjacency_verts; // the 'left' and 'right' vertices of the adjacency matrix defining a graph
		int num_vertices;			// The number of vertices in the graph
		
	public:
		// active contstructors
		Graph();
		
		~Graph();
	
		// public member functions/variables
		bool load(const char *f_name); // Creates the graph using the file passed into the function.
									   // Returns false if the file cannot be found, else returns true.
		
		void display(); // Displays the graph's adjacency matrix
		
		void displayDFS(int vertex); // Displays the result of a depth first search starting at 
									 // the provided vertex
		
		void displayBFS(int vertex); // Displays the result of a breadth first search starting at 
									 // the provided vertex
		
};




#endif