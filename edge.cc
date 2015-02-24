#include "edge.h"
 
// Edge constructor
Edge::Edge() 
{
	this->source = -1;
	this->destination = -1;
	this->weight = -1;
}

Edge::Edge(float weight)
{
	this->source = -1;
	this->destination = -1;
	this->weight = weight;
}

// CREATE CONNECTION
void Edge::CreateConnection(Vertex& source, Vertex& destination) 
{
	this->source = source.GetName();
	this->destination = destination.GetName();
}
 
// GET WEIGHT
float Edge::GetWeight()
{
	return this->weight;
}

// GET SOURCE
Vertex Edge::GetSource(NetworkGraph& graph)
{
	return graph[this->source];
}

// GET DESTINATION
Vertex Edge::GetDestination(NetworkGraph& graph)
{
	return graph[this->destination];
}

// PRINT 
void Edge::Print()
{
	std::cout << "Edge (";
	std::cout << this->GetWeight();
	std::cout << "), Src: ";
	std::cout << this->source;
	std::cout << ", Dst: ";
	std::cout << this->destination << std::endl;
}