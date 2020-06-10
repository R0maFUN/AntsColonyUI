#include "vertex.h"


VERTEX::VERTEX(u_int id, vertexTYPE type, double x, double y)
{
	this->id = id;
	this->type = type;
	this->x = x;
	this->y = y;
	if (type != warehouse)
	{
		this->capacity = const_RetailCAPACITY;
		this->filledCapacity = 0;
	}
}

VERTEX::VERTEX(u_int id, vertexTYPE type, u_int capacity, double x, double y)
{
	this->id = id;
	this->type = type;
	this->x = x;
	this->y = y;
	this->capacity = capacity;
	this->filledCapacity = 0;
}

VERTEX::VERTEX(u_int id, vertexTYPE type, u_int capacity, double x, double y, int readyTime, int dueTime)
{
	this->id = id;
	this->type = type;
	this->x = x;
	this->y = y;
	this->capacity = capacity;
	this->filledCapacity = 0;
	this->readyTime = readyTime;
	this->dueTime = dueTime;
}

VERTEX* VERTEX::clone()
{
	VERTEX* copy = new VERTEX;
	copy->id = this->id;
	copy->type = this->type;
	copy->x = this->x;
	copy->y = this->y;
	copy->capacity = this->capacity;
	copy->filledCapacity = this->filledCapacity;
	copy->readyTime = this->readyTime;
	copy->dueTime = this->dueTime;
	//map<VERTEX*, double>* tstMap = new map<VERTEX*, double>;
	//	*tstMap = *this->pheromones;
	//copy->pheromones = tstMap;

	//map<VERTEX*, double>* dstMap = new map<VERTEX*, double>; 
	//*dstMap = *this->distances;
	//copy->distances = dstMap;
	return copy;
}

void VERTEX::FillCapacity(TRUCK* truck)  
{
	if (this->filledCapacity == this->capacity)
		return;
	else if (this->filledCapacity + truck->GetFilledCapacity() > this->capacity)
	{
		truck->ChangeFilledCapacity(this->filledCapacity - this->capacity);
		this->filledCapacity = this->capacity;
	}
	else
	{
		this->filledCapacity += truck->GetFilledCapacity();
		truck->ChangeFilledCapacity(-1 * truck->GetFilledCapacity());
	}
}