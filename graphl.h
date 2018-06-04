/*                                                                                                              #THE KILLER BUNNY
Robert Boyer                                                                                                         (\_/)
CSS 343 (Fall 2015)                                                                                                  (o o)
-------------------------------------------------------------------------------------------------------------       (     )
Creation Date: 10/28/2015
Date of Last Modification: 11/12/2015
--------------------------------------------------------------------------------------------------------------------------------
Purpose: Assignment to implement Depth-First search algorithm
--------------------------------------------------------------------------------------------------------------------------------
Notes: This class creates a non-weighted graph with nodes that are connected together.
Read data file named "data32.txt"; find and display the depth-first algorithm corresponding to the nodes that have been added.
--------------------------------------------------------------------------------------------------------------------------------
*/
#ifndef GRAPHL_H
#define GRAPHL_H

#include "nodedata.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int const MAXNODE = 100;                                       //the Max number of Nodes

struct EdgeNode;                                                //forward reference for the compiler

struct GraphNode {                                              //structs used for simplicity
	EdgeNode* edgeHead;                                         //head of the list of edges
	NodeData* data;                                             //data information about each node
	bool visited;                                               //bool flags if visited
};

struct EdgeNode {                                               
	int adjGraphNode;                                           //subscript of the adjacent graph node
	EdgeNode* nextEdge;                                         //next node
};


class GraphL {

public:
	GraphL();                                                   //Default Constructor
	~GraphL();                                                  //Destructor
	void buildGraph(ifstream&);                                 //Builds graph from reading a data file
	void displayGraph();                                        //Display each nodes info and edge in graph
	void depthFirstSearch();                                    //Does a depth-first search and displays each node in that order  


private:                                                        
	GraphNode adjList[MAXNODE + 1];                            //Array of GraphNodes
	int size;                                                   //Size of Array

	//Utility Function Added
	void dfsHelper(int);                                        //Recursive Helper method for depthfirstsearch()
};
#endif