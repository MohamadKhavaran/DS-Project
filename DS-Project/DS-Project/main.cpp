#include<iostream>
#include"KDTree.h"
#include<conio.h>
#include<list>
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

	if (inputValue == "Add-P") // Add  Pizzeria
	{
		system("cls");
		cout << "Please Enter The Pizzeria Name : " << endl;
		cin >> name;
		system("cls");

		cout << "Please Enter The X Coordinate : " << endl;
		cin >> x;
		cout << "Please Enter The Y Coordinate : " << endl;
		cin >> y;
		component* IsExsist = new component;
		IsExsist->x = x;
		IsExsist->y = y;
		if (kdTree.Search(kdTree.getHead(), IsExsist) && kdTree.getHead() != nullptr)
		{
			cout << "This Point Already Exists ! \a\n\n" << endl;
			cout << "Press Any Key ..." << endl;
			_getch();
			goto flag;
		}
		else
		{
			//kdTree.MainPoints.push_back(name);
			kdTree.insert(x, y, name, true, name);

			goto flag;
		}
	}
	else if (inputValue == "Add-Br") // Add  Pizzeria
	{
		string mainBranchName;
		system("cls");
		cout << "Please Enter The Pizzeria Name : " << endl;
		cin >> name;
		cout << "Please Enter The Main branch Name : " << endl;
		cin >> mainBranchName;
		if (kdTree.ReferComponentByName(mainBranchName) == nullptr)
		{
			system("cls");
			cout << "This Point Does Not Exist Or The Point Selected As The Main Branch Is Itself A Sub Branch  ! \a\n\n" << endl;
			cout << "Press Any Key ..." << endl;
			_getch();
			goto flag;
		}

		system("cls");

		cout << "Please Enter The X Coordinate : " << endl;
		cin >> x;
		cout << "Please Enter The Y Coordinate : " << endl;
		cin >> y;
		component* IsExsist = new component;
		IsExsist->x = x;
		IsExsist->y = y;
		if (kdTree.Search(kdTree.getHead(), IsExsist) && kdTree.getHead() != nullptr)
		{
			cout << "This Point Already Exists ! \a\n\n" << endl;
			cout << "Press Any Key ..." << endl;
			_getch();
			goto flag;
		}
		else
		{
			kdTree.insert(x, y, name, false, mainBranchName);

			goto flag;
		}
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
	else if (inputValue == "Most-Brs")
	{
		kdTree.MostBrs();
		cout << "Press Any Key ..." << endl;
		_getch();
		goto flag;
	}
	else if (inputValue == "List-Brs")
	{
		system("cls");
		cout << "Enter The Name Of The Main Branch  : \n" << endl;
		cin >> name;
		kdTree.ListBrs(name);
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