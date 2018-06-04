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

#include "graphl.h"
#include "limits.h"
#include <iomanip>
#include "string.h"


//----------------------------------------------------- (Default Constructor) --------------------------------------------------
// Description: creates an empty graph
//------------------------------------------------------------------------------------------------------------------------------
GraphL::GraphL(){

	size = 0;//there are zero nodes in graph

	for (int i = 0; i <= MAXNODE; i++){
		adjList[i].visited = false;
		adjList[i].edgeHead = NULL;
		adjList[i].data = NULL;
	}
}
//---------------------------------------------------------- (Destructor) ------------------------------------------------------
// Description: deletes all NodeData, EdgeNode.. 
//                  and GraphNode data
//------------------------------------------------------------------------------------------------------------------------------
GraphL::~GraphL() {

	for (int i = 1; i < size + 1; i++){

		adjList[i].visited = false;//set to false
		delete adjList[i].data;
		adjList[i].data = NULL;//set to NULL 

		if (adjList[i].edgeHead != NULL) {// check if index contains linked list
			
			EdgeNode* temp = adjList[i].edgeHead;//save edgeHead
			
			while (temp != NULL) {//continue to traverse & delete
				
				adjList[i].edgeHead = adjList[i].edgeHead->nextEdge;//equals nextEdge
				delete temp;//delete node
				temp = NULL;//set to NULL
				temp = adjList[i].edgeHead;//next node to delete
			}
		}
	}

}
//---------------------------------------------------------- (Build Graph) -----------------------------------------------------
// Description: builds up graph node information and.. 
//              adjacency list of edges between each 
//               node reading from a data file
//------------------------------------------------------------------------------------------------------------------------------

void GraphL::buildGraph(ifstream& infile){
	
	infile >> size;//set size of array
	string nodeName = "";
	getline(infile, nodeName);

	
	for (int i = 1; i <= size; ++i){//to insert name of edges
		
		getline(infile, nodeName);
		NodeData* tmp = new NodeData(nodeName);
		adjList[i].data = tmp;//insert object into array
	}

	int fromNode, toNode;

	// read the edge data and add to the adjacency list
	while (infile >> fromNode >> toNode) {
		
		if (fromNode == 0 && toNode == 0) break;//edge of data

		//insert the edge into the adjacency list fromNode
		if (adjList[fromNode].edgeHead == NULL) {
			
			EdgeNode* node = new EdgeNode;
			node->adjGraphNode = toNode;
			adjList[fromNode].edgeHead = node;
			adjList[fromNode].edgeHead->nextEdge = NULL;
		}
		else {
			
			EdgeNode* node = new EdgeNode;
			node->adjGraphNode = toNode;
			node->nextEdge = adjList[fromNode].edgeHead;
			adjList[fromNode].edgeHead = node;
		}
	}

}
//---------------------------------------------------------- (displayGraph) ----------------------------------------------------
// Description: displays each node information.. 
//                and edge in the graph
//------------------------------------------------------------------------------------------------------------------------------
void GraphL::displayGraph(){

	cout << "Graph:" << endl; 

	for (int i = 1; i <= size; ++i){//to print all info

		cout << "Node" << i << "      " << *adjList[i].data << endl;//print index and name of node
		
		EdgeNode* current = adjList[i].edgeHead;//node that points to head

		while (current != NULL) {//print linked list

			cout << setw(7) << "  edge " << i << "  " << current->adjGraphNode << endl;
			current = current->nextEdge;  // moved to next node
		}
	}

}
//------------------------------------------------------- (depthFirstSearch) ---------------------------------------------------
// Description: makes a depth-first search and.. 
//           displays each node in depth-first order 
//------------------------------------------------------------------------------------------------------------------------------
void GraphL::depthFirstSearch()  {

	cout << "Depth-first ordering:";

	for (int i = 1; i <= size; i++) {// 1 --> size

		if (!(adjList[i].visited))//check if node has NOT been visited 
			dfsHelper(i);//call recursive helper
	}
	cout << endl;
}
//----------------------------------------------------------- (dfsHelper) ------------------------------------------------------
// Description: recursive helper method for depthFirstSearch
//------------------------------------------------------------------------------------------------------------------------------
void GraphL::dfsHelper(int v) {

	cout << setw(2) << v;//print node
	adjList[v].visited = true;//mark node as visited
	EdgeNode* current = adjList[v].edgeHead;//pointer to the head

	while (current != NULL) {//traverse linked list

		if (!adjList[current->adjGraphNode].visited) {//check if array at index of node hasn't been visited
			dfsHelper(current->adjGraphNode);//recursive call
		}

		current = current->nextEdge;//move to next node
	}
}