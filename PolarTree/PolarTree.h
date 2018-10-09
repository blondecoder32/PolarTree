#pragma once

#define _USE_MATH_DEFINES

#include "Object.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
using namespace std;


struct List
{
	Object* o;
	List* nxt;
};

class PolarNode								//сектор круга
{
	double radius;
	double bisector;
	double omega;
	int M, m;
	int sz;
	PolarNode* leftChild;
	PolarNode* rightChild;
	PolarNode* parent;
	List *l;								//список указателей на объекты. !!! Сами объекты хранятся в массиве H.

	void insert(Object* _o);
	int size(){	return sz;	}
	void remove(Object* _o);
	void merge(List* l2);

public:
	PolarNode(double _radius, int _M);
	PolarNode(double _radius, double _bisector, double _omega, int _M);
	bool isLeaf()
	{
		return (leftChild == NULL && rightChild == NULL);
	}
	bool isOverflow()
	{
		return (size() > M);
	}
	bool isUnderflow()
	{
		return (parent->size() + parent->leftChild->size() + parent->rightChild->size() < m);
	}
	bool isRange(Object* o)
	{
		return ((o->distance <= radius) && (o->heading >= bisector - omega / 2.0 && o->heading < bisector + omega / 2.0));
	}
	bool isRoot()
	{
		return (parent == NULL);
	}
	void Remove(Object* o)
	{
		remove(o);
	}
	friend class PolarTree;
};

class PolarTree
{
	unsigned int M;
	PolarNode* root;
	void inorderTraversal(PolarNode* r);
	void print_levels(PolarNode *node, int level);

public:
	PolarTree(double R, int _M);
	~PolarTree() { delete root; }
	bool Insert(Object* o);
	bool Delete(Object* o);
	bool Bisect(PolarNode*);
	bool Merge(PolarNode *s);
	PolarNode* SearchSector(double _heading, double _distance);
	PolarNode* Update(Object* o, double _distance, double _heading);
	Object* RangeSearch(PolarNode *s, double h1, double h2, double d1, double d2);
	void Show();
};

