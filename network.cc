#include "network.h"
 
// Network constructor
Network::Network() {}

// FROM GRAPH
NetworkGraph Network::FromGraph(Graph graph)
{
	int vertices = 0;

	// autodetect number of nodes in graph
	for(unsigned int i = 0; i < graph.size(); i++)
	{
		if(i != 0 && graph[i] == INFINITY)
		{
			break;
		}

		if(graph[i] == INFINITY)
		{
			vertices = 0;
		}	
		else 
		{
			vertices++;
		}
	}

	NetworkGraph vertice_array;

	// create those nodes
	for(int i = 0; i < vertices; i++) 
	{
		std::vector<Edge> edges;

		for(int j = 0; j < vertices; j++) 
		{
			float edgeValue = graph[0];
			graph.erase(graph.begin());

			Edge newEdge(edgeValue);
			edges.push_back(newEdge);
		}

		Vertex newVertex(i, edges);
		vertice_array.push_back(newVertex);
	}

	// wire the nodes
	for(Vertex &oV : vertice_array)
	{
		for(Vertex &iV : vertice_array)
		{
			oV.AddVertice(iV);
		}
	}

	NetworkGraph final_array;

	// wire edges
	for(Vertex &v : vertice_array)
	{
		std::vector<Edge> tmp_edges;

		int i = 0;
		for(Edge &e : v.GetEdges()) {

			Vertex vCon = vertice_array[i];
			i++;
			
			e.CreateConnection(v, vCon);
			tmp_edges.push_back(e);
		}
		
		Vertex tmp_vertex(v.GetName(), tmp_edges);
		final_array.push_back(tmp_vertex);
	}

	return final_array;
}