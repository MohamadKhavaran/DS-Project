#pragma once
#include<iostream>
using namespace std;
class component
{
public:
	string name;
	int x; int y;
	component* left;
	component* right;
	char determination = '0';
	void Push(int x, int y, string name);
};

