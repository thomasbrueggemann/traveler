#include "vertex.h"
 
// Vertex constructor
Vertex::Vertex() {}
Vertex::Vertex(int name, std::vector<Edge> edges)
{
	this->name = name;
	this->edges = edges;
}

// GET NAME
int Vertex::GetName()
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
Edge* Vertex::FindEdgeTo(NetworkGraph graph, Vertex &destination)
{
	// loop all edges
	for (auto &edge : this->edges)
	{
		if(edge.GetDestination(graph).Compare(destination)) 
		{
			return &edge;
		}
	}

	return NULL;
}