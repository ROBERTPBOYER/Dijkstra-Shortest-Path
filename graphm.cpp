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

#include "graphm.h"
#include "limits.h"
#include <iomanip>


//----------------------------------------------------- (Default Constructor) --------------------------------------------------
// Description: creates an empty graph
//------------------------------------------------------------------------------------------------------------------------------
GraphM::GraphM(){

	size = 0;//there are zero nodes in graph

	for (int i = 0; i < MAXNODES; i++){ //row

		for (int j = 0; j < MAXNODES; j++){ //column

			//Initializes tables to:
			T[i][j].dist = INT_MAX; //infinity
			T[i][j].path = 0; 
			T[i][j].visited = false; 
			C[i][j] = INT_MAX; //infinity
		}
	}
}
//--------------------------------------------------------- (buildGraph) -------------------------------------------------------
// Description: builds up graph node information.. 
//             and adjacency matrix edges between.. 
//             each node reading from a data file 
//------------------------------------------------------------------------------------------------------------------------------
void GraphM::buildGraph(ifstream& infile){

	infile >> size; //takes size
	
	string nodeName = ""; //empty string
	getline(infile, nodeName); //stores string in nodeName 

	for (int i = 1; i <= size; i++){//for loop to get node names 
		data[i].setData(infile);//set node names
	}

	int p1;//point 1 (from) 
	int p2;//point 2 (to)
	int w;//weight (distance between)

	while (infile >> p1 >> p2 >> w){

		if (p1 == 0 || p2 == 0 || w == 0)//stop if any zeros
			break;

		insertEdge(p1, p2, w);//add weight between the two nodes
	}

}
//--------------------------------------------------------- (insertEdge) -------------------------------------------------------
// Description: inserts an edge into graph between.. 
//          two given nodes and the weight between them
//------------------------------------------------------------------------------------------------------------------------------
void GraphM::insertEdge(const int from, const int to, const int distance){
	
	if (from >= 1 && from <= size){ //validates nodes are inside table's parameters
		
		if (to >= 1 && to <= size){ 
			
			if (distance >= 0 && distance <= INT_MAX){
				
				C[from][to] = distance;//inserts edge with distance 
			}
		}
	}
}
//--------------------------------------------------------- (removeEdge) -------------------------------------------------------
// Description: remove an edge between to give nodes
//------------------------------------------------------------------------------------------------------------------------------
void GraphM::removeEdge(const int from, const int to){
	
	if (from >= 1 && from <= size){
		 
		if (to >= 1 && to <= size){//validates nodes are inside table's parameters
		
			C[from][to] = INT_MAX;//removes edge by setting value to infinity
		}
	}
}
//------------------------------------------------------ (findShortestPath) ----------------------------------------------------
// Description: finds the shortest path between.. 
//     every node to every other node in the graph
//------------------------------------------------------------------------------------------------------------------------------
void GraphM::findShortestPath(){

	int v = 0;//holds the current smallest unvisited distance
	int w = 0;//holds current position

	for (int source = 1; source <= size; source++){
		
		T[source][source].dist = 0;//distance from itself to itself = 0

		//finds the shortest distance from source to all other nodes
		for (int j = 1; j < size; j++){

			v = nextValue(T[source]);//not visited, shortest distance at this point 
			T[source][v].visited = true;//mark visited

			for (int i = 1; i <= size; i++){//for each w adjacent to v
				
				w = i;//assign current position
				
				if (T[source][w].visited == false && C[v][w] != INT_MAX){//if w is not visited AND v->w is a path
					
					if (!(T[source][w].dist < (T[source][v].dist + C[v][w]))){//if going through v is faster than w(current)
						
						T[source][w].dist = (T[source][v].dist + C[v][w]);//update distance
						T[source][w].path = v;//make v path

					}
				   //else going through w(current) is faster so dont change path			
				}
			}
		}
	}
}

//--------------------------------------------------------- (nextValue) --------------------------------------------------------
// Description: uses 1D array containing distances to..
//		       find shortest distance up to current.. 
//             point that has not been visited
//------------------------------------------------------------------------------------------------------------------------------
int GraphM::nextValue(TableType arr[]){
	
	int lowIdx = 1;//saves low index, or lowest unmarked V
	int lowValue = INT_MAX; //saves lowIdx value; initialize value to infinity

	for (int i = 1; i < size + 1; i++){

		if (arr[i].visited == false && arr[i].dist < lowValue){//if v isn't visited & distance is less then other

			lowIdx = i;//saves index
			lowValue = arr[i].dist;//saves index value
		}
	}
	return lowIdx; //Return found v
}


//--------------------------------------------------------- (displayAll) -------------------------------------------------------
// Description: displays - description, from node, to node..
//               dijkstra's, and path of data passed in
//------------------------------------------------------------------------------------------------------------------------------
void GraphM::displayAll(){
	
	//prints header/initial line
	cout << "Description              From Node    To Node    Dijikstra's     Path" << endl;

	//nested loop for printing all data
	for (int i = 1; i < size + 1; i++){

		cout << data[i] << endl; //prints the name of nodes

		for (int j = 1; j < size + 1; j++){

			if (T[i][j].dist > 0 && T[i][j].dist < INT_MAX){

				cout << setw(31) << right << i << setw(10) << j;
				cout << setw(15) << T[i][j].dist << setw(10);
				getPath(i, j);//calls recursive helper to print path between given nodes
				cout << endl;
			}
			else
				if (i != j){ //No path and no cost
				cout << setw(31) << right << i << setw(10) << j << setw(15);
				cout << "----" << setw(10) << endl;
				}
		}
	}
	cout << endl;
}

//---------------------------------------------------------- (display) ---------------------------------------------------------
// Description: takes two intergers corresponding to nodes.. 
//              and displays source, destination, path, 
//              distance,and the names of of of the paths
//------------------------------------------------------------------------------------------------------------------------------
void GraphM::display(const int fromNode, const int toNode){

	if (T[fromNode][toNode].dist != INT_MAX){//if distance does not equal infinity, i.e. there is a path
	
		cout << fromNode << "      " << toNode << "      ";
		cout << T[fromNode][toNode].dist << "        ";
		getPath(fromNode, toNode);//calls recursive helper to print path between given nodes
		cout << endl;
	}
	else{ //it does equal infinity, i.e. there is NOT a path
	
		cout << left << setw(12) << fromNode << setw(12) << toNode;
		cout << "----        ";
	}

	getData(fromNode, toNode); //calls recursive helper to find/display data between given nodes
	cout << endl;
}
//---------------------------------------------------------- (getData) ---------------------------------------------------------
// Description: helper method for display(), recursively..
//              finds/displays data for given edge distance
//------------------------------------------------------------------------------------------------------------------------------
void GraphM::getData(int from, int to){

	if (T[from][to].dist == INT_MAX)//path DNE (does not exist)
		return;
	
	if (from == to) {//start of data
		cout << data[to] << endl;//print data 
		return;
	}
	int point = to;//hold data
	getData(from, to = T[from][to].path);	//recursive call 
	cout << data[point] << endl;//print data 
}
//---------------------------------------------------------- (getPath) ---------------------------------------------------------
// Description: helper method for display() and displayAll()
//             recursively finds path for a given edge
//------------------------------------------------------------------------------------------------------------------------------
void GraphM::getPath(int from, int to){
	
	if (T[from][to].dist == INT_MAX)//path DNE (does not exist)
		return;
	
	if (from == to) {//start of path

		cout << to << " ";//print path
		return;
	}
	int point = to;//hold path
	getPath(from, to = T[from][to].path);//recursive call
	cout << point << " ";//print path
}