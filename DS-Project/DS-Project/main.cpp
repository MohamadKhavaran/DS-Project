#include<iostream>
#include"KDTree.h"
#include<conio.h>
using namespace std;

int main()
{
	KDTree kdTree;

flag:
	string inputValue;
	system("cls");
	cout << "Enter Your Operation : " << endl;
	cin >> inputValue;
	float x;
	float y;
	string name;
	//if (inputValue == "Add-N") // Add Neighborhood
	//{
	//	system("cls");
	//	cout << "Please Enter The Neighbourhood Name : " << endl;
	//	cin >> name;
	//	system("cls");
	//	for (int i = 4; i != 0; i--)
	//	{
	//		cout << "Please Enter The X Coordinate : " << endl;
	//		cin >> x;
	//		cout << "Please Enter The Y Coordinate : " << endl;
	//		cin >> y;
	//		kdTree.insert(x, y, name);
	//		system("cls");
	//	}
	//	goto flag;
	//}
	if (inputValue == "Search")
	{
		system("cls");
		cout << "Please Enter The X Coordinate : " << endl;
		cin >> x;
		cout << "Please Enter The Y Coordinate : " << endl;
		cin >> y;
		component* IsExsist = new component;
		IsExsist->x = x;
		IsExsist->y = y;
		kdTree.Search(kdTree.getHead(), IsExsist);
	}
	else if (inputValue == "Add-P") // Add  Pizzeria
	{
		system("cls");
		cout << "Please Enter The Pizzeria Name : " << endl;
		cin >> name;
		system("cls");

		cout << "Please Enter The X Coordinate : " << endl;
		cin >> x;
		cout << "Please Enter The Y Coordinate : " << endl;
		cin >> y;
		/*component* IsExsist = new component;
		IsExsist->x = x;
		IsExsist->y = y;
		if (kdTree.Search(kdTree.getHead(), IsExsist) && kdTree.getHead() != nullptr)
		{
			cout << "This Point Already Exists ! \a\n\n" << endl;
			cout << "Press Any Key ..." << endl;
			_getch();
			goto flag;
		}*/
		//else
		//{
			kdTree.insert(x, y, name);

			goto flag;
		//}
	}
	else if (inputValue == "Near-P")
	{
		system("cls");

		cout << "Please Enter The X Coordinate : " << endl;
		cin >> x;
		cout << "Please Enter The Y Coordinate : " << endl;
		cin >> y;
		component* Target = new component;
		Target->x = x;
		Target->y = y;
		double best_dist = std::numeric_limits<double>::infinity();
		component* best = NULL;

		best = kdTree.findNearestNeighbor(kdTree.getHead(), Target, best, best_dist, true);
		system("cls");
		cout << "NearestNeighbor Is : " << "(" << best->x << "," << best->y << ") Point\n\n\n" << endl;
		cout << "Press Any Key ..." << endl;
		_getch();
		goto flag;
	}
	else if (inputValue == "Del-Br")
	{
		system("cls");
		cout << "Please Enter The X Coordinate : " << endl;
		cin >> x;
		cout << "Please Enter The Y Coordinate : " << endl;
		cin >> y;
		component* Target = new component;
		Target->x = x;
		Target->y = y;
		kdTree.Delete(Target);
		cout << "Press Any Key ..." << endl;
		_getch();
		goto flag;
	}
	else
	{
		system("cls");
		cout << "Wrong !\a\n" << endl;
		cout << "Press Any Key ..." << endl;
		_getch();
		goto flag;
	}
	return  0;
}