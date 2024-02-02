#include<iostream>
#include<list>
#include<string>

using namespace std;

struct pizzaStoreInfo {
	string name;
};


class HashTable {
private:
	int size;
	list<pizzaStoreInfo>* table;

public:
	HashTable(int size);

	int hashFunction(string key);

	void insertItem(string key, pizzaStoreInfo value);

	void deleteItem(string key);

	bool searchItem(string key);
};