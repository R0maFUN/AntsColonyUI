#include "AntsAlgorithm.h"
#include <stdlib.h>

int LinearSearchID(vector<double> array, double target)
{
	int i = 0;
	for (i; i < array.size(); ++i)
	{
		if (target <= array[i])
			return i;
	}
}

int LinSrch(vector<VERTEX*> verts, VERTEX* targ)
{
	for (int i = 0; i < verts.size(); ++i)
	{
		if (verts[i]->GetID() == targ->GetID())
			return i;
	}
	return -1;
}

u_int GetNextVertexID(VERTEX* current, vector<VERTEX*> vertexes)
{
	vector<double> probabilities;
	double sum = 0;
	double weight;
	for (auto i : vertexes)
	{
		if (current->GetID() == i->GetID())
			continue;
		weight = current->GetPheromone(i) + 1 / current->GetDistance(i);
		sum += weight;
		probabilities.push_back(sum);
	}

	for (int i = 0; i < probabilities.size(); ++i)
		probabilities[i] /= sum;
	
	double rand0to1 = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
	int result = LinearSearchID(probabilities, rand0to1);
	int id =  (LinSrch(vertexes, current) >=0 && result >= LinSrch(vertexes , current) ) ? result + 1 : result;
	return vertexes[id]->GetID();
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

void DecreasePheromones(vector <VERTEX*>& vertexes , double vaporizeSpeed)
{
	for (auto i : vertexes) // decreasing all the pheromones 
	{
		for (int j = i->GetID() + 1; j < vertexes.size(); ++j)
		{
			i->ChangePheromone(vertexes[j], (1 - vaporizeSpeed) * i->GetPheromone(vertexes[j]));
		}
	}
}

void TruckRide(vector <VERTEX*>& vertexesOrig, vector<VERTEX*>& vertexes , TRUCK* currentTruck, double PheromoneAdded , double& totalDistance, vector<VERTEX>& way, vector<EDGE>& edges)
{


	u_int destID = GetNextVertexID(vertexesOrig[currentTruck->GetCurrentVertexID()], vertexes);
	//destID = LinSrch(vertexes, vertexesOrig[destID]);
	VisitVertex(currentTruck, vertexesOrig[destID]);

	VERTEX* currentVertex = vertexesOrig[currentTruck->GetCurrentVertexID()];//LinSrch(vertexes, vertexesOrig[currentTruck->GetCurrentVertexID()]) >= 0 ? vertexes[LinSrch(vertexes, vertexesOrig[currentTruck->GetCurrentVertexID()])] : vertexesOrig[currentTruck->GetCurrentVertexID()]; //= vertexes[ LinSrch(vertexes, vertexesOrig[currentTruck->GetCurrentVertexID()]) ];
	//way.push_back(*currentVertex);

	VERTEX* destVertex = vertexesOrig[destID];
	way.push_back(*destVertex);
	EDGE edge;
	edge.from = currentVertex;
	edge.dest = destVertex;
	edge.truckID = currentTruck->GetID();
	edges.push_back(edge);
	totalDistance += currentVertex->GetDistance(destVertex);
	if (PheromoneAdded == 0)
		currentVertex->AddPheromone(destVertex, (static_cast<double> (1) / currentVertex->GetDistance(destVertex) )*5 );
	else
		currentVertex->AddPheromone(destVertex, PheromoneAdded);
	//vertexesOrig[currentTruck->GetCurrentVertexID()] = currentVertex;
	currentTruck->Ride(destVertex);
	if (destID != 0 && vertexesOrig[destID]->GetFilledCapacity() == vertexesOrig[destID]->GetCapacity())
		vertexes.erase(vertexes.begin() + LinSrch(vertexes , vertexesOrig[destID]) );

	/*
	u_int destID = GetNextVertexID(vertexesOrig[currentTruck->GetCurrentVertexID()], vertexes);
	destID = LinSrch(vertexes, vertexesOrig[destID]);
	VisitVertex(currentTruck, vertexes[destID]);
	
	VERTEX* currentVertex = LinSrch(vertexes, vertexesOrig[currentTruck->GetCurrentVertexID()]) >= 0 ? vertexes[LinSrch(vertexes, vertexesOrig[currentTruck->GetCurrentVertexID()])] : vertexesOrig[currentTruck->GetCurrentVertexID()]; //= vertexes[ LinSrch(vertexes, vertexesOrig[currentTruck->GetCurrentVertexID()]) ];
	
	VERTEX* destVertex = vertexes[destID];
	totalDistance += currentVertex->GetDistance(destVertex);
	if (PheromoneAdded == 0)
		currentVertex->AddPheromone(destVertex, static_cast<double> (1) / currentVertex->GetDistance(destVertex));
	else
		currentVertex->AddPheromone(destVertex, PheromoneAdded);
	vertexesOrig[currentTruck->GetCurrentVertexID()] = currentVertex;
	currentTruck->Ride(destVertex);
	if (destID != 0 && vertexes[destID]->GetFilledCapacity() == vertexes[destID]->GetCapacity())
		vertexes.erase(vertexes.begin() + destID);
	*/
}

//void MakeSolution(vector<VERTEX*>& vertexes, vector<TRUCK*>& trucks, double vaporizeSpeed, double PheromoneAdded , double& totalDistance, vector<VERTEX>& way)
//{
//	vector<VERTEX*> vertexesCopy = vertexes;
//	//transform(vertexes.begin(), vertexes.end(), back_inserter(vertexesCopy), cloneFunctor());
//
//	while (vertexesCopy.size() > 1)
//	{
//		for (auto truck : trucks)
//		{
//			while (truck->GetFilledCapacity() > 0 && vertexesCopy.size() > 1)
//			{
//				TruckRide(vertexes, vertexesCopy, truck, PheromoneAdded, totalDistance, way, edges);
//				DecreasePheromones(vertexesCopy, vaporizeSpeed);
//				//Sleep(300);
//			}
//		}
//	}
//
//}