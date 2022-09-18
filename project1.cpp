// Computing Structures Fall 2022
// DSA 5005
// Aditya Narasimhan

#include <iostream>
#include <string>

using namespace std;

// class node to store one node's details
class Node {
protected:
	int nodeNumber; // field to store node's number
	string nodeInfo; // field to store node's information
public:
	Node (); // default constructor
	// getters
	string getNodeInfo (); 
	int getNodeNumber ();
	// setters
	void setNodeInfo (string newInfo);
	void setNodeNumber (int newNum);

	void display(); // display node details 
};

Node::Node()
{
	nodeNumber = 0;
	nodeInfo = "";
}

string Node::getNodeInfo()
{
	return nodeInfo;
}

int Node::getNodeNumber()
{
	return nodeNumber;
}

void Node::setNodeInfo(string newInfo)
{
	nodeInfo = newInfo;
}

void Node::setNodeNumber(int newNum)
{
	nodeNumber = newNum;
}

void Node::display()
{
	cout << nodeNumber << ": " << nodeInfo << endl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// class to store one edge's details
class Edge {
protected:
	Node* u; // field to store source node pointer
	Node* v; // field to store destination node pointer
	string edgeInfo; // field to store edge information
public:
	Edge (); // default constructor
	// getters 
	Node* getu (); 
	Node* getv ();
	string getEdgeInfo();
	// setters
	void setu (Node* newu);
	void setv (Node* newv);
	void setEdgeInfo (string newInfo);

	void display(); // display edge details
};

Edge::Edge()
{
	u = NULL;
	v = NULL;
	edgeInfo = "";
}

Node* Edge::getu()
{
	return u;
}

Node* Edge::getv()
{
	return v;
}

string Edge::getEdgeInfo()
{
	return edgeInfo;
}

void Edge::setu(Node* newu)
{
	u = newu;
}

void Edge::setv(Node* newv)
{
	v = newv;
}

void Edge::setEdgeInfo(string newInfo)
{
	edgeInfo = newInfo;
}

void Edge::display()
{
	if((u != NULL) && (v != NULL))
		cout << u->getNodeInfo() << " - " << v->getNodeInfo() << " "  << edgeInfo << endl;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// class to store the graph
class GraphDB {
	protected:
		Node* myNodes; // array of nodes 
		Edge* myEdges; // array of edges
		int numNodes; // number of nodes
		int numEdges; // number of edges
		int maxEdges; // store the max number of edges (array size)
	public:
		GraphDB (int nNodes, int nEdges); // non-default constructor
		//setters
		void setNode (Node& newNode); 
		void setEdge (Edge& newEdge);
		void setNodeInfo (int u, string newInfo);
		void setEdgeInfo (int u, int v, string newInfo);

		// getters
		Node* getNode (int nodeNum);
		string getNodeInfo (int nodeNum);
		Edge* getEdgeInfo (int u, int v);

		// operations
		bool isAnEdge (int u, int v); // is this edge existent
		void addEdge (Edge& newEdge); // add an edge
		void deleteEdge (int u, int v); // delete the edge
		void display(); // display the contents of the two arrays 
};

GraphDB::GraphDB(int nNodes, int nEdges)
{
	numNodes = nNodes;
	maxEdges = nEdges;
	myNodes = new Node[numNodes]; // allocating memory for the myNodes array
	myEdges = new Edge[maxEdges]; // allocating memory for the myEdges array
	numEdges = 0; // to keep count of the number of edges currently present
}

// display for the nodes and edges of graphDB
void GraphDB::display()
{
	// cout << "numNodes: " << numNodes << endl;
	// cout << "maxEdges: " << maxEdges << endl;
	// cout << "numEdges: " << numEdges << endl;
	
	cout << "Displaying myNodes: " << endl;
	for(int i = 0; i < numNodes; i++)
		myNodes[i].display(); // calling the Node class display

	cout << "Displaying myEdges: " << endl;
	for (int i = 0; i < numEdges; i++)
		myEdges[i].display(); // calling the Edge class display
}

// setter for node object
void GraphDB::setNode(Node &newNode){
	myNodes[newNode.getNodeNumber()].setNodeNumber(newNode.getNodeNumber());
	myNodes[newNode.getNodeNumber()].setNodeInfo(newNode.getNodeInfo());

	// myNodes[newNode.getNodeNumber()] = newNode;

}

// getter for a specific node from myNodes
Node *GraphDB::getNode(int nodeNum)
{
	return &myNodes[nodeNum];
}

void GraphDB::setEdge(Edge& newEdge)
{
	numEdges++;
	// cout << "numEdges: " << numEdges << endl;
	if(numEdges >= maxEdges) // to allocate new memory
	{
		Edge* tempArrayEdges = new Edge[maxEdges + (maxEdges/2)]; // create a new temp array

		// cout << "--- Increasing the size of array by " << (maxEdges/2); 
		// cout << " new maxEdges: " << maxEdges + (maxEdges/2) << endl;
		
		for(int i = 0; i < maxEdges; i++) // copy old values - deep copy
			tempArrayEdges[i] = myEdges[i];
		
		delete [] myEdges; // delete the pointer to the old values

		myEdges = tempArrayEdges; // re point the pointer to the new memory location

		maxEdges = maxEdges + (maxEdges/2); // update the value of maxEdges
	}

	// copying the newEdge to the array
	myEdges[numEdges-1].setu((newEdge.getu()));
	myEdges[numEdges-1].setv((newEdge.getv()));
	myEdges[numEdges-1].setEdgeInfo(newEdge.getEdgeInfo());

}

void GraphDB::deleteEdge(int u, int v)
{
	if(isAnEdge(u, v)) // check if the edge is existent
	{
		for(int i = 0; i < numEdges; i++)
		{
			if (myEdges[i].getu()->getNodeNumber() == u && // loop through and find the edge
				myEdges[i].getv()->getNodeNumber() == v)
			{
				// setting the values to NULL (edge to be deleted)
				Node* t = NULL; // temp dummy node
				myEdges[i].setu(t); 
				myEdges[i].setv(t);
				myEdges[i].setEdgeInfo("");

				for(int j = i; j < numEdges - 1; j++) // left shift all the edges
				{
					myEdges[j].setu(myEdges[j+1].getu());
					myEdges[j].setv(myEdges[j+1].getv());
					myEdges[j].setEdgeInfo(myEdges[j+1].getEdgeInfo());
				}
				numEdges = numEdges - 1; // decrement the numEdges
				break;
			}
		}
	}
	else
	{
		cout << "Edge does not exist to be deleted" << endl; // this could be an exception
	}
}

// set the information of node u
void GraphDB::setNodeInfo(int u, string newInfo)
{
	for (int i = 0; i < numNodes; i++) // loop through the myNodes array
	{
		if (myNodes[i].getNodeNumber() == u ) // check nodeNum
		{
			myNodes[i].setNodeInfo(newInfo);
		}
	}
}


// set the information of edge u-v
void GraphDB::setEdgeInfo(int u, int v, string newInfo)
{
	for (int i = 0; i < numEdges; i++) // loop through the myEdges array
	{
		if (myEdges[i].getu()->getNodeNumber() == u && 
				myEdges[i].getv()->getNodeNumber() == v) // check nodeNums
		{
			myEdges[i].setEdgeInfo(newInfo);
		}
	}
}

// check the existence of an edge
bool GraphDB::isAnEdge(int u, int v)
{
	for (int i = 0; i < numEdges; i++) // loop through the myEdges array
	{
		if (myEdges[i].getu()->getNodeNumber() == u && 
				myEdges[i].getv()->getNodeNumber() == v) // check nodeNums
		{
			return true; // return true if found
		}
	}
	return false; // else false
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main()
{
	int numNodes; // temp variable to store numNodes from input
	int maxEdges; // temp variable to store numEdges from input
	int nodeNumber; 
	string nodeString;

	GraphDB* masterGraph; // pointer object of GraphDB class

	int inputU, inputV; 
	string edgeString;

	cin >> numNodes >> maxEdges; // read the numNodes and numEdges from redirected input

	// display the values read in
	cout << "numNodes: " << numNodes << endl;
	cout << "maxEdges: " << maxEdges << endl << endl;

	masterGraph = new GraphDB(numNodes, maxEdges); // allocate memory by calling non-default constructor

	// read in the information from the input
	Node tempNode;

	for (int i = 0; i < numNodes; i++)
	{
		cin >> nodeNumber >> nodeString; // read in the node details
		// cout << nodeNumber << ": " << nodeString << endl;
		tempNode.setNodeNumber(nodeNumber); // create the temp object
		tempNode.setNodeInfo(nodeString);
		masterGraph->setNode(tempNode); // insert the temp object
	}

	char command; // variable to receive the command
	Edge tempEdge;

	while(cin >> command)
	{
		switch (command)
		{
			case 'I':
				{
					cin >> inputU >> inputV >> edgeString; // read in the edge details
					cout << "Inserting " << inputU << " " << inputV << ": " << edgeString << endl;
					tempEdge.setu(masterGraph->getNode(inputU)); // create the temp edge
					tempEdge.setv(masterGraph->getNode(inputV));
					tempEdge.setEdgeInfo(edgeString);

					masterGraph->setEdge(tempEdge); // set temp edge to the myEdges array
					break;
				}
			case 'R':
				{
					cin >> inputU >> inputV; // read in the edge details
					cout << "Removing the item " << inputU << " " << inputV << endl;
					masterGraph->deleteEdge(inputU, inputV); // delete the edge in myEdges array

					break;
				}
			case 'D':
				{
					masterGraph->display(); // call display of graphDB
					break;
				}
			case 'E':
				{
					cin >> inputU >> inputV; // read in the edge details

					bool flag = masterGraph->isAnEdge(inputU, inputV);
					if(flag == true)
						cout << "Edge exists between " << masterGraph->getNode(inputU)->getNodeInfo() << " and " << masterGraph->getNode(inputV)->getNodeInfo() << endl;
						// cout << "true" << endl;
					else
						cout << "No edge exists between " << masterGraph->getNode(inputU)->getNodeInfo() << " and " << masterGraph->getNode(inputV)->getNodeInfo() << endl;
					break;
				}

			default:
				cout << "Command not recognized" << endl;
				break;
		}
		cout << endl;
	}
	
	

	return 0;
}
