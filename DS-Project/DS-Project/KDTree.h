#pragma once
#include"component.h"
class KDTree
{
	component* HeadTree = nullptr;
	char determination = '0';// An attribute that holds x or y of the parent level
public:
	bool Root = false;
	void insert(float x, float y, string name);
	component* getHead();
	component* findNearestNeighbor(component*, component*, component*, double&, bool);
	bool Search(component* root, component* target);
	component* ReferComponent(float x, float y);
	void Delete(component* target);
};

