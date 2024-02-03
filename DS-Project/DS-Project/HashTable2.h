#include<iostream>
#include<list>
#include<string>

using namespace std;

struct zoneName {
	string name;
	int x1, x2, x3, x4;
	int y1, y2, y3, y4;
};


class HashTable {
private:
	int size;
	list<zoneName>* table;

public:
	HashTable(int size);

	int hashFunction(string key);

	void insertItem(string key, zoneName value);

	void deleteItem(string key);

	bool searchItem(string key);
};