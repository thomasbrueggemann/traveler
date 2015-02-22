#include "edge.h"
 
// Edge constructor
Edge::Edge() {}
Edge::Edge(float weight)
{
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