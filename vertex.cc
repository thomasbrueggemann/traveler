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

// GET EDGE
Edge Vertex::GetEdge(int idx)
{
	return this->edges[idx];
}

// GET EDGES
std::vector<Edge> Vertex::GetEdges()
{
	return this->edges;
}

// ADD VERTICE
void Vertex::AddVertice(Vertex vertex)
{
	this->vertices.push_back(vertex);
}

// GET VERTICES
std::vector<Vertex> Vertex::GetVertices()
{
	return this->vertices;
}

// COMPARE
bool Vertex::Compare(Vertex compareTo)
{
	if(this->GetName() == compareTo.GetName()) 
	{
		return true;
	}
	
	return false;
}

// FIND EDGE TO
Edge* Vertex::FindEdgeTo(Vertex &destination)
{
	// loop all edges
	for (auto &edge : this->edges)
	{
		if(edge.GetDestination().Compare(destination)) 
		{
			return &edge;
		}
	}

	return NULL;
}