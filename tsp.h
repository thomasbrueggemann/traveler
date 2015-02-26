#ifndef TSP_H
#define TSP_H

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

typedef std::vector<int> Order;
typedef std::vector<std::vector<float>> DistanceTable;

class TSP
{
private:
	DistanceTable distances;
	Order currentOrder;
	Order nextOrder;
	float shortestDistance;

	int RandomIntFromInterval(int min, int max);
	float RandomFloat();
	float GetTotalDistance(Order order);
	Order GetNextArrangement(Order order);

public:
	TSP(DistanceTable distances);
	void Anneal();
	Order GetCurrentOrder();
	float GetShortestDistance();
};

#endif