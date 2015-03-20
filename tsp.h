#ifndef TSP_H
#define TSP_H

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cmath>

typedef std::vector<int> Order;
typedef std::vector<std::vector<double>> DistanceTable;

class TSP
{
private:
	DistanceTable distances;
	Order currentOrder;
	Order nextOrder;
	double shortestDistance;

	int RandomIntFromInterval(int min, int max);
	double RandomDouble();
	double GetTotalDistance(Order order);
	Order GetNextArrangement(Order order);

public:
	TSP(DistanceTable distances);
	void Anneal();
	Order GetCurrentOrder();
	double GetShortestDistance();
};

#endif