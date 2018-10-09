#include "PolarTree.h"

void PolarNode::insert(Object* _o)
{
	if (!l && !isRoot())
	{
		l = new List;
		l->o = _o;
		l->nxt = NULL;
		sz++;
	}
	else
	{
		List* tmp = new List;
		tmp->o = _o;
		tmp->nxt = l;
		l = tmp;
		sz++;
	}
}

void PolarNode::remove(Object* _o)
{
	if (l->o == _o)
	{
		List* tmp = l->nxt;
		delete l;
		l = tmp;
		sz--;
	}
	else if (l)
	{
		for (List *p = l; p->nxt != NULL && p != NULL; )

		{
			if (p->nxt->o == _o && p->nxt != NULL)
			{
				List* tmp = p->nxt->nxt;
				delete p->nxt;
				sz--;
				p->nxt = tmp;
			}

			if (p->nxt)
			{
				p = p->nxt;
			}

		}
	}
}

void PolarNode::merge(List* l2)
{
	for (List* p = l2; p != NULL; )
	{
		List* tmp = p->nxt;
		insert(p->o);
		delete p;
		p = tmp;
	}
}

PolarNode::PolarNode(double _radius, int _M)
{
	l = NULL; sz = 0;
	radius = _radius;
	leftChild = rightChild = NULL;
	bisector = M_PI;
	M = _M;
	m = 0.75*M;
	omega = M_PI;
}

PolarNode::PolarNode(double _radius, double _bisector, double _omega, int _M)
{
	l = NULL; sz = 0;
	radius = _radius; bisector = _bisector;
	leftChild = rightChild = NULL;
	omega = _omega;
	M = _M;
	m = 0.75*M;
}

PolarTree::PolarTree(double R, int _M)
{
	M = _M;
	root = new PolarNode(sqrt(2)*R, M);
	root->parent = NULL;
	root->leftChild = new PolarNode(R, M_PI / 2, M_PI, M);
	root->rightChild = new PolarNode(R, 3.0*M_PI_2, M_PI, M);
	root->leftChild->parent = root->rightChild->parent = root;
}

void PolarTree::inorderTraversal(PolarNode* r)
{
	if (r != NULL)
	{
		inorderTraversal(r->leftChild);
		inorderTraversal(r->rightChild);
	}
}

void PolarTree::Show()
{
	inorderTraversal(root);
	cout << endl;
	print_levels(root, 1);
}

void PolarTree::print_levels(PolarNode *node, int level)
{
	if (node == NULL)
	{
		return;					//дерево пустое
	}

	print_levels(node->leftChild, ++level);
	for (int i = 0; i < level; i++)
	{
		cout << "|";
	}
	for (List *p = node->l; p != NULL; p = p->nxt)
	{
		cout << p->o->name << " ";
	}
	cout << endl;

	level--;
	print_levels(node->rightChild, ++level);
}

PolarNode* PolarTree::SearchSector(double _heading, double _distance)
{

	PolarNode* s = root;
	if (s->radius < _distance)
	{
		return NULL;				///объект за переделами области видимости f
	}

	while (s != NULL)
	{
		if (s->isLeaf())						//если s - лист
		{
			return s;
		}
		else if (_heading < s->bisector && _distance <= s->radius / sqrt(2.0))
		{
			s = s->leftChild;
		}
		else if (_heading >= s->bisector && _distance <= s->radius / sqrt(2.0))
		{
			s = s->rightChild;
		}
		else return s;							//поиск может закончиться на внутреннем узле
	}			
}

bool PolarTree::Insert(Object* o)
{
	PolarNode *s = SearchSector(o->heading, o->distance);
	if (s)
	{
		s->insert(o);
		if (s->isLeaf())
		{
			if (s->isOverflow())
			{
				Bisect(s);
			}
		}
		return true;
	}
	else return false;
}

bool PolarTree::Bisect(PolarNode* s)
{
	s->leftChild = new PolarNode(s->radius / sqrt(2.0), s->bisector - s->omega / 4.0, s->omega / 2.0, M);
	s->rightChild = new PolarNode(s->radius / sqrt(2.0), s->bisector + s->omega / 4.0, s->omega / 2.0, M);

	s->leftChild->parent = s->rightChild->parent = s;

	if (s->l)
	{
		List* p = s->l;
		while (p != NULL)
		{
			if (s->leftChild->isRange(p->o))
			{
				List* tmp = p->nxt;
				Object* t = p->o;
				s->remove(t);
				s->leftChild->insert(t);

				p = tmp;
			}
			else if (s->rightChild->isRange(p->o))
			{
				List* tmp = p->nxt;
				Object* t = p->o;
				s->remove(t);
				s->rightChild->insert(t);
				p = tmp;
			}
			else 
			{
				p = p->nxt;
			}
		}
	}

	return true;
}

bool PolarTree::Delete(Object* o)
{
	PolarNode *s = SearchSector(o->heading, o->distance);
	if (s)
	{
		s->remove(o);
		if (s->isLeaf())
		{
			if (s->isUnderflow())
			{
				Merge(s->parent);
			}
		}
		return true;
	}
	else return false;
}

bool PolarTree::Merge(PolarNode *s)
{
	if (s != root)
	{
		s->merge(s->leftChild->l);
		s->merge(s->rightChild->l);
		delete s->leftChild;
		delete s->rightChild;
		s->leftChild = s->rightChild = NULL;
		if (s->isUnderflow())
		{
			Merge(s->parent);
		}
		return true;

	}
	else return false;
}

PolarNode* PolarTree::Update(Object* o, double _distance, double _heading)
{
	PolarNode *s = SearchSector(o->heading, o->distance);
	if (!s) return NULL;

	if (o->distance <= _distance)
	{
		o->sign = -1;				//-, объект удаляется от f
	}
	else
	{
		o->sign = 1;				//+, объект приближается к f
	}
	if (!s->isRange(o))
	{
		s->Remove(o);				//o вышел за пределы данного сектора
		Insert(o);					//ищем новый сектор для o
	}
	else
	{
		o->distance = _distance;	//o остается в том же секторе, но обновим его расстояние до f
	}
	return s;
}

Object* PolarTree::RangeSearch(PolarNode *s, double h1, double h2, double d1, double d2)
{
	if (s != NULL)
	{
		Object* res;
		if (h1 < s->bisector && d1 <= s->radius / sqrt(2))
		{
			RangeSearch(s->leftChild, h1, h2, d1, d2);			//поиск в левом поддереве сектора s
		}

		for (List *p = s->l; p != NULL; p = p->nxt)
		{
			if ((p->o->heading >= h1 && p->o->heading<h2) && (p->o->distance>d1 && p->o->distance <= d2))
			{
				return p->o;
			}
		}

		if (h1 >= s->bisector && d1 <= s->radius / sqrt(2))
		{
			RangeSearch(s->rightChild, h1, h2, d1, d2);
		}
	}
	else return NULL;
}