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
void findNodesWithName(component* currentNode, string targetName, list<component*>& components)
{
	//This function is to find all the nodes whose main branch name is the same.
	if (currentNode == nullptr) {
		return;
	}

	if (currentNode->MainBrancheName == targetName)
	{
		components.push_back(currentNode);
	}

	findNodesWithName(currentNode->left, targetName, components);
	findNodesWithName(currentNode->right, targetName, components);
}
void KDTree::insert(float Input_x, float Input_y, string name, bool isMain, string MainBrancheName)
{
	//This function is for adding nodes to the tree, which can add both sub-branches and main branches.
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
	//This function returns a component that represents the closest node to the target
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
	//In this function, we only check whether the target exists in the tree or not
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
	//In this function, it returns a component by receiving x and y characteristics
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
void updateDetermination(component* root, char newDetermination)
{
	//This function prevents confusion of the determination attribute in each component
	if (root == NULL) {
		return;
	}

	root->determination = newDetermination;
	updateDetermination(root->left, (newDetermination == 'x' ? 'y' : 'x'));
	updateDetermination(root->right, (newDetermination == 'x' ? 'y' : 'x'));
}
void KDTree::Delete(component* target)
{
	//This function deletes the desired component. Also after deleting the appointment Taking children will be in the right place
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
	//This function receives the name of a component and returns it
	for (auto value : MainPointCopmonents)
	{
		if (value->name == name)
			return value;
	}
	return nullptr;
}
int KDTree::countComponentsWithName(component* root, string name)
{
	//This function counts the number of all components that share a specific main branch name
	if (root == nullptr) {
		return 0;
	}

	int count = 0;
	if (root->MainBrancheName == name) {
		count = 1;
	}

	return count + countComponentsWithName(root->left, name) + countComponentsWithName(root->right, name);
}
void KDTree::MostBrs()
{
	//This function specifies the component that has the largest number of children and also declares the number of its children
	if (HeadTree == nullptr)
	{
		cout << " \aThere Are No Points In This Tree !";
		return;
	}
	list<int> CountBranches;
	for (auto value : MainPointCopmonents)
	{
		CountBranches.push_back((countComponentsWithName(HeadTree, value->name)) - 1);
	}
	//bubble sort
	bool swapped = true;
	while (swapped) {
		swapped = false;
		auto it = CountBranches.begin();
		auto next = std::next(it);
		while (next != CountBranches.end()) {
			if (*it > *next) {
				std::swap(*it, *next);
				swapped = true;
			}
			it++;
			next++;
		}
	}
	component* MostBrs = new component;
	auto LastElementIterator = CountBranches.end();
	LastElementIterator--;
	int n = 0;
	for (auto Value : MainPointCopmonents)
	{
		n = countComponentsWithName(HeadTree, Value->name) - 1;
		if (n == *LastElementIterator)
		{
			MostBrs = Value;
			break;
		}
	}
	cout << "Point : " << "(" << MostBrs->x << "," << MostBrs->y << ")" << " Has " << *(LastElementIterator) << " Branches . " << endl;
	return;
}
void KDTree::ListBrs(string MainBrancheName)
{
	//This function returns the list of all sub - branches
	list<component*> Branches;
	findNodesWithName(HeadTree, MainBrancheName, Branches);
	cout << "The Branches Are : \n" << endl;
	auto ItStart = Branches.begin();
	ItStart++;
	while (ItStart != Branches.end())
	{
		cout << "(" << (*ItStart)->x << "," << (*ItStart)->y << ")" << endl;
		ItStart++;
	}
	return;
}