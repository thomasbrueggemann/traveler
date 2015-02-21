#include "edge.h"
 
// Edge constructor
Edge::Edge() {}
Edge::Edge(float weight)
{
	this->weight = weight;
}

// CREATE CONNECTION
void Edge::CreateConnection(const Vertex &source, const Vertex &destination) 
{
	this->source = &source;
	this->destination = &destination;
}
 
// GET WEIGHT
float Edge::GetWeight()
{
	return this->weight;
}

// GET SOURCE
Vertex Edge::GetSource()
{
	return *this->source;
}

// GET DESTINATION
Vertex Edge::GetDestination()
{
	return *this->destination;
}