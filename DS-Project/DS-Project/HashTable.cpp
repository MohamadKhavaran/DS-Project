#include "HashTable.h"

HashTable::HashTable(int size) {
	this->size = size;
	table = new list<pizzaStoreInfo>[size];
}


int HashTable::hashFunction(string key) {
	int sum = 0;
	for (int i = 0; key[i]; i++) {
		sum += key[i];
	}
	int result = sum % size;

	return result;
}


void HashTable::insertItem(string key, pizzaStoreInfo value) {
	int index = hashFunction(key);
	table[index].push_back(value);
}



void HashTable::deleteItem(string key) {
	int index = hashFunction(key);
	list<pizzaStoreInfo> ::iterator i;
	for (i = table[index].begin(); i != table[index].end(); i++) {
		if ((*i).name == key) {
			break;
		}
	}
	if (i != table[index].end()) {
		table[index].erase(i);
	}
}


bool HashTable::searchItem(string key){
	int index = hashFunction(key);

	for(auto input : table[index]){
		if(input.name==key)
			return true;
	}
	
	return false;
}