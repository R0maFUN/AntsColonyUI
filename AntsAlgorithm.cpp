#include "AntsAlgorithm.h"


int LinearSearchID(vector<double> array, double target)
{
	int i = 0;
	for (i; i < array.size(); ++i)
	{
		if (target <= array[i])
			return i;
	}
}
u_int GetNextVertexID(VERTEX* current, vector<VERTEX*>& vertexes)
{
	vector<double> probabilities;
	double sum = 0;
	double weight;
	for (auto i : vertexes)
	{
		if (current == i)
			continue;
		weight = current->GetPheromone(i) + 1 / current->GetDistance(i);
		sum += weight;
		probabilities.push_back(sum);
	}

	for (int i = 0; i < probabilities.size(); ++i)
		probabilities[i] /= sum;
	double rand0to1 = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
	int result = LinearSearchID(probabilities, rand0to1);
	return result >= current->GetID() ? result + 1 : result;
}

void VisitVertex(TRUCK* truck, VERTEX* vertex)
{
	if (vertex->GetType() == retailer)
		vertex->FillCapacity(truck);
	else
		truck->Load();
}

void UpdatePheromones(vector <VERTEX*>& vertexes, double vaporizeSpeed, vector<TRUCK*>& trucks, double PheromoneAdded) // PheromoneAdded - usually 1/distance ( 0 if u want to add const (1/distance))
{
	for (auto i : vertexes) // decreasing all the pheromones 
	{
		for (int j = i->GetID() + 1; j < vertexes.size(); ++j)
		{
			i->ChangePheromone(vertexes[j], (1 - vaporizeSpeed) * i->GetPheromone(vertexes[j]));
		}
	}

	for (auto currentTruck : trucks) // Doing all the trucks movements and increasing pheromones
	{
		u_int destID = GetNextVertexID(vertexes[currentTruck->GetCurrentVertexID()], vertexes);
		VisitVertex(currentTruck, vertexes[destID]);
		VERTEX* currentVertex = vertexes[currentTruck->GetCurrentVertexID()];
		VERTEX* destVertex = vertexes[destID];
		if (PheromoneAdded == 0)
			currentVertex->AddPheromone(destVertex, static_cast<double> (1) / currentVertex->GetDistance(destVertex));
		else
			currentVertex->AddPheromone(destVertex, PheromoneAdded);
		currentTruck->Ride(destVertex);
	}

}

void Initialize(vector <VERTEX*>& vertexes, vector<TRUCK*>& trucks, int truckCapacity , int trucksAmount)
{
	for (auto i : vertexes)
	{
		i->SetDistances(vertexes);
		i->SetPheromones(vertexes, 1);
	}

	for (int i = 0; i < trucksAmount; ++i)
	{
		TRUCK* truck = new TRUCK(i, truckCapacity, 0, vertexes[0]);
		trucks.push_back(truck);
	}

}
