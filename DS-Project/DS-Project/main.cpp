#include<iostream>
#include"KDTree.h"
#include<conio.h>
using namespace std;

int main()
{
	KDTree kdTree;

flag : 
	string inputValue;
	cout << "Enter Your Operation : " << endl;
	cin >> inputValue;
	if (inputValue == "Add-N")
	{
		system("cls"); 
		int x;
		int y;
		string name; 
		cout << "Please Enter The X Coordinate : " << endl;
		cin >> x; 
		cout << "Please Enter The Y Coordinate : " << endl;
		cin >> y;
		cout << "Please Enter The Neighbourhood Name : " << endl;
		cin >> name;
		kdTree.insert(x,y,name); 
		goto flag;
	}
	else
	{ 
		system("cls");
		cout << "Input Is Invalid !\a" << endl;
		goto flag;
	}
	return  0;
}