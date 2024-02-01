#include "KDTree.h"
#include<conio.h>
void KDTree::insert(int Input_x, int Input_y, string name)
{

	component KDComponent;
	char LorR = '0';
	KDComponent.Push(Input_x, Input_y, name);
	if (!Root) // Determine if the root (in other words Tree ) exists
	{
		KDComponent.determination = 'x';
		*HeadTree = KDComponent;//Save The Head Of Tree
		Root = true;
		system("cls");
		return;
	}
	component* TravelingComponent = HeadTree;
	component* Temp = HeadTree;
	while (TravelingComponent != NULL)
	{
		if (TravelingComponent->determination == 'x')
		{
			if (KDComponent.x < TravelingComponent->x)
			{
				Temp = TravelingComponent;
				LorR = 'L';
				determination = TravelingComponent->determination;
				TravelingComponent = TravelingComponent->left;
			}
			else
			{
				Temp = TravelingComponent;
				LorR = 'R';
				determination = TravelingComponent->determination;
				TravelingComponent = TravelingComponent->right;
			}
		}
		else if (TravelingComponent->determination == 'y')
		{
			if (KDComponent.y < TravelingComponent->y)
			{
				Temp = TravelingComponent;
				LorR = 'L';
				determination = TravelingComponent->determination;
				TravelingComponent = TravelingComponent->left;
			}
			else
			{
				Temp = TravelingComponent;
				LorR = 'R';
				determination = TravelingComponent->determination;
				TravelingComponent = TravelingComponent->right;
			}
		}
	}
	
	if (determination == 'x')
		KDComponent.determination = 'y';
	else
		KDComponent.determination = 'x';
	if (LorR == 'L')
	{
		Temp->left = new component;
		*Temp->left = KDComponent;
	}
	if (LorR == 'R')
	{
		Temp->right = new component;
		*Temp->right = KDComponent;
	}
	system("cls");
}