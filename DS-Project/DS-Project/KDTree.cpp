#include "KDTree.h"
#include<conio.h>
#include <algorithm>
#include <cmath>
component* KDTree::getHead()
{
	return HeadTree;
}
component* Minimum(component* root)
{
	component* current = root;
	while (current->left != nullptr)
	{
		current = current->left;
	}
	return current;
}
void KDTree::insert(float Input_x, float Input_y, string name, bool isMain, string MainBrancheName)
{
	component* KDComponent = new component;
	KDComponent->MainBrancheName = MainBrancheName;
	KDComponent->IsMain = isMain;
	char LorR = '0';
	KDComponent->Push(Input_x, Input_y, name);
	if (isMain == true)
		MainPointCopmonents.push_back(KDComponent); // Save The Main Points For Search By Name
	if (!Root) // Determine if the root (in other words Tree ) exists
	{
		KDComponent->determination = 'x';
		HeadTree = new component;
		HeadTree = KDComponent;//Save The Head Of Tree
		HeadTree->LorR = '0';
		Root = true;
		return;
	}
	component* TravelingComponent = HeadTree;
	component* Temp = HeadTree;
	while (TravelingComponent != NULL)
	{
		if (TravelingComponent->determination == 'x')
		{
			if (KDComponent->x < TravelingComponent->x)
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
			if (KDComponent->y < TravelingComponent->y)
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

	if (determination == 'x')//Determine whether to compare at each level through x or through y
		KDComponent->determination = 'y';
	else
		KDComponent->determination = 'x';
	if (LorR == 'L') //Determining whether the child is left or right
	{
		Temp->left = new component;
		KDComponent->LorR = 'L';
		Temp->left = KDComponent;
		KDComponent->parent = Temp;
	}
	if (LorR == 'R')
	{
		Temp->right = new component;
		KDComponent->LorR = 'R';
		Temp->right = KDComponent;
		KDComponent->parent = Temp;
	}
	return;
}
component* KDTree::findNearestNeighbor(component* root, component* target, component* best, double& best_dist, bool split)
{
	if (root == nullptr) {
		return best;
	}

	double dist = sqrt(pow(root->x - target->x, 2) + pow(root->y - target->y, 2));

	if (dist < best_dist) {
		best = root;
		best_dist = dist;
	}

	component* near = root->left;
	component* far = root->right;

	if ((!split && target->y >= root->y) || (split && target->x >= root->x)) {
		std::swap(near, far);
	}

	best = findNearestNeighbor(near, target, best, best_dist, !split);

	if ((split && pow(target->x - root->x, 2) < best_dist) || (!split && pow(target->y - root->y, 2) < best_dist)) {
		best = findNearestNeighbor(far, target, best, best_dist, !split);
	}

	return best;
}
bool KDTree::Search(component* root, component* target)
{
	component* current = root;

	while (current != nullptr) {
		if (current->x == target->x && current->y == target->y) {
			return true;
		}

		if (target->x < current->x || (target->x == current->x && target->y < current->y)) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}

	return false;
}
component* KDTree::ReferComponent(float x, float y)
{
	component* current = HeadTree;

	while (current != nullptr) {
		if (current->x == x && current->y == y) {
			return current;
		}

		if (x < current->x || (x == current->x && y < current->y)) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	return nullptr;
}
void updateDetermination(component* root, char newDetermination) {
	if (root == NULL) {
		return;
	}

	root->determination = newDetermination;
	updateDetermination(root->left, (newDetermination == 'x' ? 'y' : 'x'));
	updateDetermination(root->right, (newDetermination == 'x' ? 'y' : 'x'));
}
void KDTree::Delete(component* target)
{
	component* current = ReferComponent(target->x, target->y);
	if (current->IsMain == true)
	{
		cout << "This pizzeria is a main branch and you cannot delete it! \a\n\n" << endl;
		return;
	}
	if (current == nullptr)
	{
		cout << "Not Found ! \a" << endl;
		return;
	}
	else if (current->left == nullptr && current->right == nullptr) // Target is  a Leaf
	{
		if (current->LorR == 'R')
			current->parent->right = nullptr;
		else
			current->parent->left == nullptr;
	}
	else if (current->left == nullptr && current->right != nullptr)
	{
		if (current->LorR == 'R')
		{
			current->parent->right = current->right;
			current->right->parent = current->parent;
			if (current->determination == 'x')
				current->right->determination = 'x';
			else
				current->right->determination = 'y';
		}
		else
		{
			current->parent->left = current->right;
			current->right->parent = current->parent;
			if (current->determination == 'x')
				current->right->determination = 'x';
			else
				current->right->determination = 'y';
		}

	}
	else if (current->left != nullptr && current->right == nullptr)
	{
		if (current->LorR == 'R')
		{
			current->parent->right = current->left;
			current->left->parent = current->parent;
			if (current->determination == 'x')
				current->left->determination = 'x';
			else
				current->left->determination = 'y';
		}
		else
		{
			current->parent->left = current->left;
			current->left->parent = current->parent;
			if (current->determination == 'x')
				current->left->determination = 'x';
			else
				current->left->determination = 'y';
		}
	}
	else
	{

		component* minimum = Minimum(current->right);
		if (current->right == minimum)
		{

			minimum->parent = current->parent;
			current->parent->right = minimum;
			minimum->left = current->left;
			if (current->determination == 'x')
				minimum->determination = 'x';
			else
				minimum->determination = 'y';
			if (current->LorR == 'R')
				minimum->LorR = 'R';
			else
				minimum->LorR = 'R';
			delete current;
			return;
		}
		if (minimum->right != nullptr)
		{
			minimum->right->parent = minimum->parent;
			minimum->parent->left = minimum->right;
			updateDetermination(minimum->right, minimum->determination);
			minimum->left = current->left;
			current->left->parent = minimum;
			minimum->parent = current->parent;
			current->parent->right = minimum;
			minimum->right = current->right;
			current->right->parent = minimum;
			if (current->determination == 'x')
				minimum->determination = 'x';
			else
				minimum->determination = 'y';
			if (current->LorR == 'R')
				minimum->LorR = 'R';
			else
				minimum->LorR = 'R';
		}
		else if (minimum->right == nullptr)
		{
			minimum->parent = current->parent;
			current->parent->right = minimum;
			minimum->left = current->left;
			minimum->right = current->right;
			if (current->determination == 'x')
				minimum->determination = 'x';
			else
				minimum->determination = 'y';
		}
		if (current->LorR == 'R')
			minimum->LorR = 'R';
		else
			minimum->LorR = 'R';
	}
	delete current;
}
component* KDTree::ReferComponentByName(string name)
{
	for (auto value : MainPointCopmonents)
	{
		if (value->name == name)
			return value;
	}
	return nullptr;
}

int countComponentsWithName(component* root, string name)
{
	if (root == nullptr) {
		return 0;
	}

	int count = 0;
	if (root->MainBrancheName == name) {
		count = 1;
	}

	return count + countComponentsWithName(root->left, name) + countComponentsWithName(root->right, name);
}
string KDTree::MostBrs()
{
	if (HeadTree == nullptr)
	{
		return " There Are No Points In This Tree"; 
	}
	list<int> CountBranches;
	for (auto value : MainPointCopmonents)
	{
		CountBranches.push_back((countComponentsWithName(HeadTree, value->name))-1);  
	}
		
	}