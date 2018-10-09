#pragma once

#include <iostream>
#include <string>
using namespace std;

class Object
{
	int OID;
	double heading;
	double distance;
	string name;

	int sign;
public:
	Object() { OID = 0; heading = 0; distance = 0; name = "noname"; }
	Object(double h, double d, string n) { OID = 0; heading = h; distance = d; sign = 1; name = n; }
	Object(const Object& _o) { OID = _o.OID; heading = _o.heading; distance = _o.distance; sign = 1; name = _o.name; }

	friend class PolarNode;
	friend class PolarTree;
};
