#pragma once
#include <iostream>
#include <list>
#include <iterator>

template <typename T1,typename T2>
class Map
{
public:

	Map(); 
	~Map(); 

private:
	template<typename T1,typename T2>
	struct Node {
		Node<T1, T2>* left;
		Node<T1, T2>* right;
		Node<T1, T2>* parent;
		bool color; // 0 - black, 1 - red
		T2 data;
		T1 key;

		Node(T1 key = T1(),T2 data = T2(), Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr) {
			this->key = key;
			this->data = data;
			this->left = left;
			this->right = right;
			this->parent = parent;
			this->color = 1;
		}
	};
	Node<T1, T2>* head;
	int size;
	std::list<T1> keys;
	std::list<T2> values;
public:

	void destroy(Node<T1,T2>* temp); 

	void insert(typename T1, typename T2); 
	void balanceInsert(Node<T1,T2>* node); 

	void remove(typename T1); 
	void balanceRemove(Node<T1,T2>* node,bool side); 

	void leftRotate(Node<T1, T2>* node); 
	void rightRotate(Node<T1, T2>* node); 

	int getSize(); 
	Node<T1, T2>* getHead() const; 

	T2 find(T1 key); 
	void clear(); 

	std::list<T1> getKeys(); 
	std::list<T2> getValues(); 

	void print(Node<T1, T2>* node);
	void print();
};
