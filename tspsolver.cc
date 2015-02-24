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

	if(s.size() == 0)
	{
		return cost;
	}

	for(unsigned int node_idx = 0; node_idx < s.size() - 1; node_idx++)
	{
		Vertex node = s[node_idx];
		Vertex next_node = s[node_idx + 1];
		
		// add the costs
		Edge *edgeTo = node.FindEdgeTo(this->network, next_node);
		if(edgeTo != NULL) 
		{
			cost += edgeTo->GetWeight();

			if(DEBUG) 
			{
				std::cout << "cost of edge ";
				std::cout << edgeTo->GetWeight() << std::endl;
			}
		}

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

// GET UNVISITED NODES
Path TSPSolver::GetUnvisitedNodes(Path s)
{
	Path u;
	float currentPathCosts = 0.0;

	if(s.size() == 0)
	{
		return u;
	}

	int s_name = s[s.size() - 1].GetName();
	this->currentNode = this->network[s_name];

	if(this->cutting == true) 
	{
		currentPathCosts = this->CalculatePathCosts(s);

		if(DEBUG)
		{
			std::cout << "currentPathCosts: ";
			std::cout << currentPathCosts << std::endl;
		}
	}

	for(Edge &edge : this->currentNode.GetEdges())
	{
		if(DEBUG)
		{
			std::cout << "edge weight: ";
			std::cout << edge.GetWeight() << std::endl;
		}

		// filter impossible edges (loops or cuts)
		if(edge.GetWeight() == INFINITY)
		{
			continue;
		}

		bool continuing = false;

		// it was already visited
		for(Vertex &visitedNode : this->v[s.size() - 1])
		{
			Vertex dest = edge.GetDestination(this->network);
			if(visitedNode.Equals(dest))
			{
				if(DEBUG)
				{
					std::cout << "already visited" << std::endl;
					visitedNode.Print();
				}

				continuing = true;
				break;
			}
		}

		if(continuing) continue;

		// they are our parents, so we visited them already
		for(Vertex &currentPathNode : s)
		{
			Vertex dest = edge.GetDestination(this->network);
			if(currentPathNode.Equals(dest))
			{
				if(DEBUG)
				{
					std::cout << "parent already visited" << std::endl;
					currentPathNode.Print();
				}

				continuing = true;
				break;
			}
		}

		if(continuing) continue;

		bool unvisited = true;

		if(this->cutting == true)
		{
			if((currentPathCosts + edge.GetWeight()) >= this->best_cost)
			{
				// cut suboptimal path
				Vertex destination = edge.GetDestination(this->network);
				this->v[s.size() - 1].push_back(destination);
				unvisited = false; 
			}
		}

		if(unvisited)
		{
			Vertex destination = edge.GetDestination(this->network);
			u.push_back(destination);
		}
	}

	return u;
}

// SOLVE
// Solve the traveling salesman problem through an iterative backtracking
void TSPSolver::Solve(int max_steps)
{
	float starttime;

	if(DEBUG) 
	{
		std::cout << "start tsp solving" << std::endl;
		starttime = duration_cast< milliseconds >(
		    high_resolution_clock::now().time_since_epoch()
		).count();
	}

	// push our root path and its already visited nodes if we do not have some prepared path (sub-tree solving)
	if(this->s.size() == 0) 
	{
		this->s.push_back(this->currentNode);

		std::vector<Vertex> empty;
		this->v.push_back(empty);
	}

	while(this->s.size() > 0)
	{
		if(max_steps-- <= 0) 
		{
			return;
		}

		this->u = this->GetUnvisitedNodes(this->s);

		if(DEBUG)
		{
			std::cout << "unvisited nodes: ";
			std::cout << this->u.size() << std::endl;
		}

		// traverse unvisited
		if(this->u.size() > 0)
		{
			// reset visited nodes for upcoming layer
			std::vector<Vertex> empty;

			if(this->v.size() == 0) {
				std::vector<std::vector<Vertex>> tmp_v;
				this->v = tmp_v;
			}

			this->v[this->s.size()] = empty;

			if(this->min_heuristic)
			{
				// sort by min path
				sortstruct s(this);
				std::sort(this->u.begin(), this->u.end(), s);
			}

			this->currentNode = this->u[0];
			this->u.erase(this->u.begin());
			this->s.push_back(this->currentNode);
		}

		// no traversal possible
		else
		{
			// calculate pathcosts if we are in a complete path
			if(this->s.size() == this->network.size())
			{
				float pathCost = this->CalculatePathCosts(this->s); 
				if(pathCost < this->best_cost)
				{
					this->best_cost = pathCost;
					Path bestPath(this->s);
					this->best_path = bestPath;

					// TODO: callback best costs
				}
			}

			if(this->s.size() > 1)
			{
				Vertex tmp = this->s.back();

				if(DEBUG)
				{
					std::cout << this->s.size() << std::endl;
				}

				this->v[this->s.size() - 2].push_back(tmp);
				this->s.pop_back();
				this->currentNode = this->s[this->s.size() - 1];
			}
			// end of tree, finish
			else 
			{
				// we pop our root node, so we are done
				this->s.pop_back();
			}
		}

		// we got a complete path, print it
		if(this->s.size() == this->network.size() && DEBUG)
		{
			for(Vertex &node : this->s)
			{
				std::cout << node.GetName() << std::endl;
			}

			float endtime = duration_cast< milliseconds >(
			    high_resolution_clock::now().time_since_epoch()
			).count();

			float duration = endtime - starttime;
			std::cout << "tsp solving took ";
			std::cout << duration;
			std::cout << " milliseconds" << std::endl;
		}
	}
}

// GET BEST PATH
Path TSPSolver::GetBestPath()
{
	return this->best_path;
}