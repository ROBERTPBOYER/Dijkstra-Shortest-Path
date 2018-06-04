/*                                                                                                              #THE KILLER BUNNY
Robert Boyer                                                                                                         (\_/)
CSS 343 (Fall 2015)                                                                                                  (o o)
-------------------------------------------------------------------------------------------------------------       (     )
Creation Date: 10/28/2015
Date of Last Modification: 11/12/2015
--------------------------------------------------------------------------------------------------------------------------------
Purpose: Assignment to implement Dijkstra's shortest path algorithm
--------------------------------------------------------------------------------------------------------------------------------
Notes: This class creates a weighted graph with nodes that are connected together. 
	   Read data file named "data31.txt"; find the lowest cost path; display cost/path from every node to every other node.
--------------------------------------------------------------------------------------------------------------------------------
*/

#ifndef GRAPHM_H
#define GRAPHM_H

#include "nodedata.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int const MAXNODES = 100;                                       //the Max number of Nodes

class GraphM {
	
public:
	GraphM();                                                   // Default Constructor
	void buildGraph(ifstream&);                                 // Builds Graph based on input file 
	void insertEdge(const int, const int, const int);           // Inserts an edge between two Nodes
	void removeEdge(const int, const int);                      // Removes an edge between two Nodes
	void findShortestPath();                                    // Finds the shortest path between every node to every other node in the graph
	void displayAll();                                          // Uses couts to demonstrate that the algorithm works properly
	void display(const int, const int);                         // Displays shortest distance with path info between from/to Nodes


private:

	NodeData data[MAXNODES];               // Data for graph nodes
	int C[MAXNODES][MAXNODES];             // Cost array, the adjacency matrix
	int size;                              // Number of nodes in the graph

	struct TableType {                     
		bool visited;                      // Whether node has been visited
		int dist;                          // Shortest distance from source known so far
		int path;                          // Previous node in path of min dist
	};

	TableType T[MAXNODES][MAXNODES];       // Stores visited, distance, path

	//Utility Functions Added
	int nextValue(TableType[]);  //Helper method for findShortestPath()
	void getPath(int, int);      //Helper method for display() and displayAll()
	void getData(int, int);      //Helper method for display()
};

#endif