#pragma once
#include"component.h"
class KDTree
{
	component* HeadTree = new component;
	char determination = '0';
public:
	bool Root = false;
	void insert(int x, int y, string name);
};

