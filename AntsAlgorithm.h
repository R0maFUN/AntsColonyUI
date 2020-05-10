#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <time.h>
#include <Windows.h>
#include "vertex.h"
#include "truck.h"
#include <conio.h>
#include "ReadData.h"
using namespace std;

#define const_TruckCAPACITY 50;
#define const_RetailCAPACITY 460;

typedef unsigned int u_int;

int LinearSearchID(vector<double> array, double target);

u_int GetNextVertexID(VERTEX* current, vector<VERTEX*>& vertexes);

void VisitVertex(TRUCK* truck, VERTEX* vertex);
void UpdatePheromones(vector <VERTEX*>& vertexes, double vaporizeSpeed, vector<TRUCK*>& trucks, double PheromoneAdded); // PheromoneAdded - usually 1/distance ( 0 if u want to add const (1/distance))
void Initialize(vector <VERTEX*>& vertexes, vector<TRUCK*>& trucks, int truckCapacity, int trucksAmount);
