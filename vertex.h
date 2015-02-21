#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <string>
#include <vector>

#include "edge.h"

class Edge;
class Vertex
{
private:
	std::string name;
	std::vector<Edge> edges;
	std::vector<Vertex> vertices; // adjacent vertices

public:
	Vertex();
	Vertex(std::string name, std::vector<Edge> edges);
	std::string GetName();
	Edge GetEdge(int idx);
	std::vector<Edge> GetEdges();
	void AddVertice(Vertex vertex);
	std::vector<Vertex> GetVertices();
	bool Compare(Vertex compareTo);
	Edge* FindEdgeTo(Vertex &destination);
};

#endif