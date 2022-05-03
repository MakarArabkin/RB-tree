#include "Map.h"

template <typename T1, typename T2>
Map<T1, T2>::Map() {
	head = nullptr;
	size = 0;
}

template <typename T1, typename T2>
Map<T1, T2>::~Map() {
	destroy(head);
}

template <typename T1, typename T2>
void Map<T1, T2>::destroy(Node<T1, T2>* temp) {
	if (temp == nullptr) return;
	destroy(temp->left);
	destroy(temp->right);
	if (temp->parent && temp->parent->left == temp) temp->parent->left = nullptr;
	else if (temp->parent) temp->parent->right = nullptr;
	delete temp;
	size--;
}

template <typename T1, typename T2>
void Map<T1, T2>::insert(T1 key, T2 data) {
	Node<T1, T2>* newNode = new Node<T1, T2>(key, data);
	Node<T1, T2>* temp = head;
	bool flag = 0;

	if (head == nullptr) {
		newNode->color = 0;
		size++;
		head = newNode;
		keys.push_back(newNode->key);
		values.push_back(newNode->data);
		return;
	}

	while (!flag) {
		if (newNode->key == temp->key) return;
		else if (newNode->key < temp->key) {
			if (temp->left == nullptr) {
				temp->left = newNode;
				newNode->parent = temp;
				flag = 1;
				size++;
				keys.push_back(newNode->key);
				values.push_back(newNode->data);
			}
			else temp = temp->left;
		}
		else {
			if (temp->right == nullptr) {
				temp->right = newNode;
				newNode->parent = temp;
				flag = 1;
				size++;
				keys.push_back(newNode->key);
				values.push_back(newNode->data);
			}
			else temp = temp->right;
		}
	}
	balanceInsert(newNode);
	head->color = 0;
}

template <typename T1, typename T2>
void Map<T1, T2>::balanceInsert(Node<T1, T2>* node) {
	if (node->parent == nullptr) return;
	if (!node->parent->color) return;
	if (node->parent->parent == nullptr) {
		node->parent->color = 0;
		return;
	}

	bool parent_info; // 0 - left, 1 - right
	if (node->parent->parent->left == node->parent) parent_info = 0;
	else parent_info = 1;

	bool node_info; // 0 - left, 1 - right
	if (node->parent->left == node) node_info = 0;
	else node_info = 1;

	if (parent_info) {
		if (!node->parent->parent->left || !node->parent->parent->left->color) {
			if (node_info) {
				leftRotate(node->parent->parent);
				node->parent->color = 0;
				node->parent->left->color = 1;
			}
			else {
				rightRotate(node->parent);
				leftRotate(node->parent);
				node->color = 0;
				node->left->color = 1;
			}
		}
		else {
			node->parent->color = 0;
			if (node->parent->parent->left)node->parent->parent->left->color = 0;
			node->parent->parent->color = 1;
			balanceInsert(node->parent->parent);
		}
	}
	else {
		if (!node->parent->parent->right || !node->parent->parent->right->color) {
			if (!node_info) {
				rightRotate(node->parent->parent);
				node->parent->color = 0;
				node->parent->right->color = 1;
			}
			else {
				leftRotate(node->parent);
				rightRotate(node->parent);
				node->color = 0;
				node->right->color = 1;
			}
		}
		else {
			node->parent->color = 0;
			if (node->parent->parent->right)node->parent->parent->right->color = 0;
			node->parent->parent->color = 1;
			balanceInsert(node->parent->parent);
		}
	}
}

template <typename T1, typename T2>
void Map<T1, T2>::remove(T1 key) {
	Node<T1, T2>* temp = head;
	bool flag = 0;
	if (head->key == key && size == 1) {
		keys.remove(head->key);
		values.remove(head->data);
		delete head;
		head = nullptr;
	}
	while (!flag) {
		if (temp == nullptr) return;
		else if (temp->key == key) {
			flag = 1;
			keys.remove(temp->key);
			values.remove(temp->data);
		}
		else if (temp->key < key) temp = temp->right;
		else temp = temp->left;
	}

	keys.remove(temp->key);
	auto iter = values.end();
	iter--;
	if (*iter == temp->data) values.pop_back();
	else {
		for (auto iter = values.begin(); iter != values.end(); iter++)
		{
			if (*iter == temp->data) {
				iter = values.erase(iter);
				break;
			}
		}
	}

	int count = (temp->left != nullptr) + (temp->right != nullptr);

	if (count == 2) {
		Node<T1, T2>* buff = temp;
		buff = temp->right;
		while (buff->left)buff = buff->left;
		temp->data = buff->data;
		temp->key = buff->key;
		temp = buff;
		count = (temp->left != nullptr) + (temp->right != nullptr);
	}
	if (count == 1) {
		if (temp->left) {
			temp->key = temp->left->key;
			temp->data = temp->left->data;
			temp = temp->left;
		}
		else {
			temp->key = temp->right->key;
			temp->data = temp->right->data;
			temp = temp->right;
		}
		count = (temp->left != nullptr) + (temp->right != nullptr);
	}
	if (count == 0) {
		if (temp->color) {
			if (temp->parent->left == temp) temp->parent->left = nullptr;
			else temp->parent->right = nullptr;
			delete temp;
			size--;
		}
		else {
			bool side; // 0 - left, 1 - right
			if (temp->parent->left == temp) temp->parent->left = nullptr, side = 0;
			else temp->parent->right = nullptr, side = 1;
			Node<T1, T2>* p = temp->parent;
			delete temp;
			size--;
			balanceRemove(p, side);
		}
	}
}

template <typename T1, typename T2>
void Map<T1, T2>::balanceRemove(Node<T1, T2>* node, bool side) {
	if (side) {
		if (node->color && !node->left->color && (!node->left->left || !node->left->left->color) && (!node->left->right || !node->left->right->color))
		{
			node->color = 0;
			node->left->color = 1;
		}
		else if (node->color && !node->left->color && node->left->left != nullptr && node->left->left->color)
		{
			node->color = 0;
			node->left->color = 1;
			node->left->left->color = 0;
			rightRotate(node);
		}
		else if (!node->color && node->left->color && node->left->right != nullptr && !node->left->right->color && (!node->left->right->left || !node->left->right->left->color) && (!node->left->right->right || !node->left->right->right->color))
		{
			node->left->color = 0;
			node->left->right->color = 1;
			rightRotate(node);
		}
		else if (!node->color && node->left->color && node->left->right != nullptr && !node->left->right->color && node->left->right->left != nullptr && node->left->right->left->color)
		{
			node->left->right->left->color = 0;
			leftRotate(node->left);
			rightRotate(node);
		}
		else if (!node->color && !node->left->color && node->left->right != nullptr && node->left->right->color)
		{
			node->left->right->color = 0;
			leftRotate(node->left);
			rightRotate(node);
		}
		else if (!node->color && !node->left->color && (!node->left->right || !node->left->right->color) && (!node->left->left || !node->left->left->color))
		{
			node->left->color = 1;
			if (node->parent) {
				if (node->parent->left == node) balanceRemove(node->parent, 0);
				else balanceRemove(node->parent, 1);
			}
		}
	}
	else {
		if (node->color && !node->right->color && (!node->right->left || !node->right->left->color) && (!node->right->right || !node->right->right->color)) {
			node->color = 0;
			node->right->color = 1;
		}
		else if (node->color && !node->right->color && node->right->right != nullptr && node->right->right->color) {
			node->color = 0;
			node->right->color = 1;
			node->right->right->color = 0;
			leftRotate(node);
		}
		else if (!node->color && node->right->color && node->right->left != nullptr && !node->right->left && (!node->right->left->left || !node->right->left->left->color) && (!node->right->left->right || !node->right->left->right->color)) {
			node->right->color = 1;
			node->right->left->color = 0;
			leftRotate(node);
		}
		else if (!node->color && node->right->color && node->right->left != nullptr && !node->right->left->color && node->right->left->right != nullptr && node->right->left->right->color) {
			node->right->left->right->color = 0;
			rightRotate(node->right);
			leftRotate(node);
		}
		else if (!node->color && !node->right->color && node->right->left != nullptr && node->right->left->color) {
			node->right->left->color = 1;
			rightRotate(node->right);
			leftRotate(node);
		}
		else if (!node->color && !node->right->color && (!node->right->left || !node->right->left->color) && (!node->right->right || !node->right->right->color)) {
			node->right->color = 1;
			if (node->parent) {
				if (node->parent->left == node) balanceRemove(node->parent, 0);
				else balanceRemove(node->parent, 1);
			}
		}
	}
}

template <typename T1, typename T2>
void Map<T1, T2>::leftRotate(Node<T1, T2>* node) {
	if (node->right == nullptr) return;

	Node<T1, T2>* temp = node->right;

	if (node == head) head = temp;

	node->right = temp->left;
	if (temp->left)temp->left->parent = node;

	if (node->parent) {
		if (node->parent->left == node) node->parent->left = temp;
		else node->parent->right = temp;
	}
	temp->parent = node->parent;

	node->parent = temp;
	temp->left = node;

}

template <typename T1, typename T2>
void Map<T1, T2>::rightRotate(Node<T1, T2>* node) {
	if (node->left == nullptr) return;

	Node<T1, T2>* temp = node->left;

	if (node == head) head = temp;

	node->left = temp->right;
	if (temp->right)temp->right->parent = node;

	if (node->parent) {
		if (node->parent->left == node) node->parent->left = temp;
		else node->parent->right = temp;
	}
	temp->parent = node->parent;

	node->parent = temp;
	temp->right = node;

}

template <typename T1, typename T2>
int Map<T1, T2>::getSize() {
	return size;
}

template <typename T1, typename T2>
Map<T1, T2>::Node<T1, T2>* Map<T1, T2>::getHead() const {
	return this->head;
}

template <typename T1, typename T2>
void Map<T1, T2>::print(Node<T1, T2>* node) {
	if (node == NULL)
		return;
	if (node->parent == NULL)
		std::cout << node->key << " : " << node->data << "(" << node->color << ") is root" << '\n';
	else if (node->parent->left == node)
	{
		std::cout << node->key << " : " << node->data << "(" << node->color << ") is " << node->parent->data << "'s " << "left child" << '\n';
	}
	else
	{
		std::cout << node->key << " : " << node->data << "(" << node->color << ") is " << node->parent->data << "'s " << "right child" << '\n';
	}
	print(node->left);
	print(node->right);
}

template <typename T1, typename T2>
void Map<T1, T2>::print() {
	if (head == NULL)
		std::cout << "empty RBtree\n";
	else
		print(head);
}

template <typename T1, typename T2>
T2 Map<T1, T2>::find(T1 key) {
	Node<T1, T2>* temp = head;
	bool flag = 0;
	while (!flag) {
		if (temp->key == key) break;
		else if (temp->key < key) {
			if (temp->right) temp = temp->right;
			else break;
		}
		else {
			if (temp->left) temp = temp->left;
			else break;
		}
	}
	return temp->data;
}

template <typename T1, typename T2>
void Map<T1, T2>::clear() {
	destroy(head);
	head = nullptr;
}

template <typename T1, typename T2>
std::list<T1> Map<T1, T2>::getKeys() {
	return this->keys;
}

template <typename T1, typename T2>
std::list<T2> Map<T1, T2>::getValues() {
	return this->values;
}