// Developer: Willie Gross
// Graph.cpp

// Purpose: Implements the Graph data structure and DFS/BFS functionality 
//			as defined in Graph.h 

// NOTE: Compile with "g++ -std=c++11 ... "

// Function Libraries
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include "Graph.h"

using namespace std;

// Constructor and memeber-function implementations
Graph::Graph()
{
	index_matrix = nullptr;
	num_vertices = 0;
}

Graph::~Graph()
{
	if(index_matrix != nullptr)
	{
		for(int i = 0; i < num_vertices; i++){
			delete index_matrix[i];
		}
		delete index_matrix;
	}
}

bool Graph::load(const char *f_name)
{	
	// Variables used in file-reading and parsing
	string line, fname = f_name;
	int temp, vert1, vert2;
	bool first_line = true;
	ifstream inFile;
	
	inFile.open(fname.c_str());
	
	if (inFile.fail()) 
	{
		return false;
	}

	// Read vertex/edge data according to pre-defined input file formatting rules
	while(getline(inFile, line)){
		istringstream iss(line);
		while(iss >> temp){
			if(first_line)
			{
				num_vertices = temp;
				
				index_matrix = new int*[num_vertices];
		
				for(int i = 0; i < num_vertices; i++){
					index_matrix[i] = new int[num_vertices];
				}
				first_line = false;
			}
			else
			{
				adjacency_verts.push(temp);
			}
		}
	}
	
	// Zero-out the adjacency matrix
	for(int i = 0; i < num_vertices; i++){
		for(int j = 0; j < num_vertices; j++){
			index_matrix[i][j] = 0;
		}
	}
	
	// Populate and mirror* the adjacency matrix
	while(!adjacency_verts.empty()){
		vert1 = adjacency_verts.front(); adjacency_verts.pop();
		vert2 = adjacency_verts.front(); adjacency_verts.pop();
		
		index_matrix[vert1][vert2] = 1;
		index_matrix[vert2][vert1] = 1; //*
	}	
	
	return true;
}

void Graph::display()
{
	if(index_matrix != nullptr)
	{
		cout << endl;
		for(unsigned int i = 0; i < num_vertices; i++){
			for(unsigned int j = 0; j < num_vertices; j++){
				cout << index_matrix[i][j] << ' ';
			}
			cout << endl;
		}
	}
	else
	{
		cout << "The graph is empty..." << endl;
	}
	return;
}

void Graph::displayBFS(int vertex)
{
	if(num_vertices == 0)
	{
		cout << "Graph is empty..." << endl;
		return;
	}
	
    bool *visited = new bool[num_vertices];
    for(int i = 0; i < num_vertices; i++)
        visited[i] = false;
 
    queue<int> BFSqueue;
 
    // Mark the current node as visited and enqueue it
    visited[vertex] = true;
    BFSqueue.push(vertex);
 
	int iter; // used to grab the adjacent vertices of the current vertex
 
    while(!BFSqueue.empty())
    {
        // Dequeue a vertex from BFSqueue and print it
        vertex = BFSqueue.front();
        cout << vertex << " ";
        BFSqueue.pop();
 
        // Grab all adjacent vertices and enqueue if not already visited
        for(int i = 0; i < num_vertices; i++)
        {
			if(index_matrix[vertex][i] == 1)
			{
				if(!visited[i])
				{
					visited[i] = true;
					BFSqueue.push(i);
				}
			}
        }
    }
	cout << endl;
	delete visited;
	
	return;
}
 
void Graph::displayDFS(int vertex)
{
	if(num_vertices == 0)
	{
		cout << "Graph is empty..." << endl;
		return;
	}
	
    // Initialize all vertices to not visited
    bool *visited = new bool[num_vertices];
    for (int i = 0; i < num_vertices; i++)
        visited[i] = false;
 
    // Call the recursive helper function to print DFS traversal
    DFS_helper(vertex, visited);
	
	return;
}

void Graph::DFS_helper(int vertex, bool visited[])
{
    // Mark vertex visited and print
    visited[vertex] = true;
    cout << vertex << " ";
 
    // Call for each adjacent vertex
    int iter;
    for (int i = 0; i < num_vertices; i++){
		if(index_matrix[vertex][i] == 1)
		{
			if (!visited[i])
			{
				DFS_helper(i, visited);
			}
		}
	}
	return;
}