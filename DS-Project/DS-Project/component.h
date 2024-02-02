#pragma once
#include<iostream>
using namespace std;
class component
{
public:
	string name;
	float x; float y; 
	component* left;
	component* right;
	component* parent; 
	char LorR;
	bool IsMain; 
	char determination = '0';//Specifies whether to check x or y to add each node 
	void Push(float x, float y, string name);
};

