#include "vertex.h"
 
// Vertex constructor
Vertex::Vertex() {}
Vertex::Vertex(std::string name, std::vector<Edge> edges)
{
	this->name = name;
	this->edges = edges;
}

// GET NAME
std::string Vertex::GetName()
{
	return this->name;
}