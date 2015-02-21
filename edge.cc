#include "edge.h"
 
// Edge constructor
Edge::Edge(float weight)
{
	this->weight = weight;
}

// CREATE CONNECTION
void Edge::CreateConnection(Vertex source, Vertex destination) 
{
	this->between[0] = source;
	this->between[1] = destination;
}
 
// GET WEIGHT
float Edge::GetWeight()
{
	return this->weight;
}

// GET SOURCE
Vertex Edge::GetSource()
{
	return this->between[0];
}

// GET DESTINATION
Vertex Edge::GetDestination()
{
	return this->between[1];
}