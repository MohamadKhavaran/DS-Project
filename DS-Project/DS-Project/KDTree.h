#pragma once
#include"component.h"
#include<list>
class KDTree
{
	component* HeadTree = nullptr;
	char determination = '0';// An attribute that holds x or y of the parent level
	int countComponentsWithName(component* root, string name); 
public:
	list<component*>MainPointCopmonents; 
	bool Root = false;
	void insert(float x, float y, string name, bool isMain, string MainBrancheName);
	component* getHead();
	component* findNearestNeighbor(component*, component*, component*, double&, bool);
	bool Search(component* root, component* target);
	component* ReferComponent(float x, float y);
	void Delete(component* target);
	component* ReferComponentByName(string name); 
	string MostBrs();
};

