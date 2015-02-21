#include "tspsolver.h"

// CONSTRUCTOR
TSPSolver::TSPSolver(NetworkGraph network, int start_node)
{
	this->network = network;

	this->best_cost = INFINITY;
	this->cutting = true;
	this->min_heuristic = true;

	this->SetStartNode(start_node);
}

// CALCULATE PATH COSTS
// Calculates the cost for the given path through the given weights
float TSPSolver::CalculatePathCosts(Path s)
{
	float cost = 0.0;

	for(unsigned int node_idx = 0; node_idx < s.size() - 1; node_idx++)
	{
		Vertex node = s[node_idx];
		Vertex next_node = s[node_idx + 1];
		
		// add the costs
		Edge *edgeTo = node.FindEdgeTo(next_node);
		cost += edgeTo->GetWeight();
	}

	return cost;
}

// SET START NODE
// Set the node of where to start
// (Calling this is only reasonable before solving the problem)
void TSPSolver::SetStartNode(int start_node)
{
	this->currentNode = this->network[start_node];
}

// SET PARTIAL PROBLEM
// This function is used to define a partial problem which then gets solved.
// Every Path which would be some kind of parent will be marked as already solved.
/*void TSPSolver::SetPartialProblem(Path path)
{
	if(path.size() > this->network.size()) 
	{
		throw "Path can not be longer then network!";
	}

	// reset our state
	this->s.clear();
	this->v.clear();
	this->u.clear();

	int pathIdx = 0;
	for(Vertex &pathValue : path)
	{
		Vertex currentDepthNode = this->network[];
		pathIdx++;
	}
}*/

Path TSPSolver::GetUnvisitedNodes(Path s)
{
	Path u;
	float currentPathCosts = 0.0;

	if(s.size() == 0)
	{
		return u;
	}

	std::string s_name = s[s.size()].GetName();
	this->currentNode = this->network[boost::lexical_cast<int>(s_name)];

	if(this->cutting == true) 
	{
		currentPathCosts = this->CalculatePathCosts(s);
	}

	for(Edge &edge : this->currentNode.GetEdges())
	{
		// filter impossible edges (loops or cuts)
		if(edge.GetWeight() == INFINITY)
		{
			u.empty();
			return u;
		}

		// it was already visited
		for(Vertex &visitedNode : this->v[s.size() - 1])
		{
			if(visitedNode.Compare(edge.GetDestination()) == true)
			{
				u.empty();
				return u;
			}
		}

		// they are our parents, so we visited them already
		for(Vertex &currentPathNode : s)
		{
			if(currentPathNode.Compare(edge.GetDestination()) == true)
			{
				u.empty();
				return u;
			}
		}

		bool unvisited = true;

		if(this->cutting == true)
		{
			if((currentPathCosts + edge.GetWeight()) >= this->best_cost)
			{
				// cut suboptimal path
				Vertex destination = edge.GetDestination();
				this->v[s.size() - 1].push_back(destination);
				unvisited = false; 
			}
		}

		if(unvisited == true)
		{
			Vertex destination = edge.GetDestination();
			u.push_back(destination);
		}
	}

	return u;
}

// SOLVE
// Solve the traveling salesman problem through an iterative backtracking
void TSPSolver::Solve(int max_steps)
{
	milliseconds starttime;

	if(DEBUG) 
	{
		starttime = duration_cast< milliseconds >(
		    high_resolution_clock::now().time_since_epoch()
		);
	}

	// push our root path nd its already visited nodes if we do not have some prepared path (sub-tree solving)
	if(this->s.size() == 0) 
	{
		this->s.push_back(this->currentNode);
		//std::vector<Vertex> empty;
		//this->v.push_back(empty);
	}

	while(this->u.size() > 0)
	{
		if(max_steps-- <= 0) 
		{
			break;
		}

		this->u = this->GetUnvisitedNodes(this->s);

		// traverse unvisited
		if(this->u.size() > 0)
		{
			// reset visited nodes for upcoming layer
			std::vector<Vertex> empty;
			this->v[this->s.size()] = empty;

			if(this->min_heuristic == true)
			{
				// sort by min path
				std::sort(this->u.begin(), this->u.end(), 
					[this] (const Vertex a, const Vertex b) -> bool
					{ 
						Edge *eA = a.FindEdgeTo(currentNode);
						Edge *eB = b.FindEdgeTo(currentNode);

						return (eA->GetWeight() < 
							   	eB->GetWeight()); 
					} 
				);
			}
		}
	}
}