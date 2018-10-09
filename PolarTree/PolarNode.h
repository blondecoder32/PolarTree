#pragma once

#include "Source.h"
class PolarNode						//сектор круга
{
	double radius;
	double bisector;
	double omega;
	int M;

	PolarNode* leftChild;
	PolarNode* rightChild;
	Object **h;				//указатель на массив-список объектов

public:
	PolarNode(double _radius, double _bisector, double _omega, int _M)
	{
		radius = _radius; bisector = _bisector; h = new Object*[M]; leftChild = rightChild = NULL; omega = _omega;
	}
	~PolarNode()
	{
		for (int i = 0; i < M; i++)
		{
			delete h[i];
		}
		delete[] h;
	}
	bool isLeaf()
	{
		return (leftChild == NULL && rightChild == NULL);
	}
	bool isOverflow();
	bool isRange(Object* o);
	friend class PolarTree;
};


bool PolarNode::isRange(Object* o)
{
	return (o->distance <= radius && (o->heading >= bisector - omega / 2.0 && o->heading < bisector + omega / 2.0));
}


