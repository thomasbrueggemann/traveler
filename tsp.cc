#include "tsp.h"

// TSP
TSP::TSP(DistanceTable distances) 
{
	this->distances = distances;
	this->shortestDistance = 0.0;

	// init the current order
	for(int i = 0; i < distances.size(); i++)
	{
		this->currentOrder.push_back(i);
	}
}

// RANDOM INT FROM INTERVAL
int TSP::RandomIntFromInterval(int min, int max)
{
	std::mt19937 rng(seed);
	std::uniform_int_distribution<int> gen(min, max); // uniform, unbiased

	return gen(rng);
}

// RANDOM FLOAT FROM INTERVAL
float TSP::RandomFloatFromInterval(float min, float max)
{
	std::default_random_engine generator;
 	std::uniform_real_distribution<float> distribution(min, max);

 	return distribution(generator);
}

// GET TOTAL DISTANCE
float TSP::GetTotalDistance(Order order)
{
	float distance;

	for(int i = 0; i < order.size(); i++)
	{
		int a = order[i];
		int b = order[i + 1];
		distance += this->distances[a][b];
	}

	if(order.size() > 1)
	{
		int last = order[order.size() - 1];
		distance += this->distances[last][0];
	}

	return distance;
}

// GET NEXT ARRANGEMENT
Order TSP::GetNextArrangement(Order order)
{
	Order newOrder;

	for(int i = 0; i < order.length; i++)
	{
		newOrder.push_back(i);
	}

	// we will only rearrange two points by random
	// starting point should always be zero - so zero should not be included
	int firstRandomIdx = this->RandomIntFromInterval(1, newOrder.size() - 2);
	int secondRandomIdx = this->RandomIntFromInterval(1, newOrder.size() - 2);

	int dummy = newOrder[firstRandomIdx];
	newOrder[firstRandomIdx] = newOrder[secondRandomIdx];
	newOrder[secondRandomIdx] = dummy;

	return newOrder; 
}

// ANNEAL
void Anneal()
{
	int iteration = -1;

	float temperature = 10000.0;
	float distanceDelta = 0.0;
	float coolingRate = 0.9999;
	float absoluteTemperature = 0.00001;

	float distance = this->GetTotalDistance(this->currentOrder);

	while(temperature > absoluteTemperature)
	{
		this->nextOrder = this->GetNextArrangement(this->currentOrder);
		distanceDelta = this->GetTotalDistance(this->nextOrder) - distance;

		// if the new order has a smaller distance
		// or if the new order has a larger distance but satisfies the Boltzman condition 
		// then accept the arrangement
		if((distanceDelta < 0) || (distanceDelta >= 0 && std::exp(-distanceDelta / temperature) > this->RandomFloatFromInterval(0.0, 1.0)))
		{
			for(int i = 0; i < this->nextOrder.size(); i++)
			{
				this->currentOrder[i] = this->nextOrder[i];
			}

			distance = distanceDelta + distance;
		}

		// cool down temperature
		temperature *= coolingRate;

		iteration++;
	}

	this->shortestDistance = distance;
}

// GET CURRENT ORDER
Order TSP::GetCurrentOrder()
{
	return this->currentOrder;
}

// GET SHORTEST DISTANCE
float TSP::GetShortestDistance()
{
	return this->shortestDistance;
}