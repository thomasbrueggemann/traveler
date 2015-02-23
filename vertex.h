#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <string>
#include <vector>

#include "edge.h"

class Vertex;
typedef std::vector<Vertex> NetworkGraph;

class Edge;
class Vertex
{
private:
	int name;
	std::vector<Edge> edges;
	std::vector<Vertex> vertices; // adjacent vertices

public:
	Vertex();
	Vertex(int, std::vector<Edge> edges);
	int GetName();
	Edge GetEdge(int idx);
	std::vector<Edge> GetEdges();
	void AddVertice(Vertex vertex);
	std::vector<Vertex> GetVertices();
	bool Equals(Vertex compareTo);
	Edge* FindEdgeTo(NetworkGraph graph, Vertex &destination);
	void Print();
};

#endif