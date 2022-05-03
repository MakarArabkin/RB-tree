#include <iostream>
#include "Map.h"
#include "Map.cpp"
#include <list>

using namespace std;

int main() {
	Map <int,int> ar;

	ar.insert(14, 2);
	ar.insert(10, 1);
	ar.insert(16, 3);
	ar.insert(20, 5);
	ar.remove(16);

	list<int> keys = ar.getKeys();
	//keys.remove(16);
	for (auto x : keys) cout << x << " ";
	cout << '\n';



	list<int> val = ar.getValues();
	for (auto x : val) cout << x << " ";
	cout << '\n';

}