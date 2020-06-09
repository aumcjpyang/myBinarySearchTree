#ifndef BST_H
#define BST_H
#include <iostream>

using namespace std;

class Node
{
public:
	Node(int _key, char _element)
	{
		key = _key;
		element = _element;
		left = right = nullptr;
	}
	int key;
	char element;
	Node* left;
	Node* right;
};

class BST
{
public:
	BST()
	{
		root = nullptr;
	}
	~BST()
	{
		if (root != nullptr)
			Release_BST(root);
	}
	void insert(int _key, char _element)
	{
		if (root == nullptr)
		{
			root = new Node(_key, _element);
		}
		else
		{
			insert(root, _key, _element);
		}
	}
	void CutOut(int _key)
	{
		if (root == nullptr)
			cout << "nothing to cut !!!" << endl;
		else
			CutOut(root, _key);
	}
	bool search(int _key) const
	{
		if (root == nullptr)
		{
			cout << "this BST is empty." << endl;
			return false;
		}
		else if (_key == root->key)
		{
			cout << "the element at key " << _key << " is " << root->element << endl;
			return true;
		}
		else
			return search(root, _key);
	}
	void printInOrder() const
	{
		if (root == nullptr)
			cout << "BST is empty." << endl;
		else
			printInOrder(root);
	}
	void printPreOrder() const
	{
		if (root == nullptr)
			cout << "BST is empty." << endl;
		else
			printPreOrder(root);
	}
	void printPostOrder() const
	{
		if (root == nullptr)
			cout << "BST is empty." << endl;
		else
			printPostOrder(root);
	}
protected:
	Node* root;
	void insert(Node* temp_node, int _key, char _element)
	{
		if (_key < temp_node->key)
		{
			if (temp_node->left == nullptr)
			{
				temp_node->left = new Node(_key, _element);
			}
			else
			{
				insert(temp_node->left, _key, _element);
			}
		}
		else
		{
			if (temp_node->right == nullptr)
			{
				temp_node->right = new Node(_key, _element);
			}
			else
			{
				insert(temp_node->right, _key, _element);
			}
		}
	}
	bool search(Node* s_node, int _key) const
	{
		if (_key < s_node->key)
			if (s_node->left == nullptr)
			{
				cout << "the " << _key << " node is not exist." << endl;
				return false;
			}
			else
				return search(s_node->left, _key);
		else if (_key > s_node->key)
			if (s_node->right == nullptr)
			{
				cout << "the " << _key << " node is not exist." << endl;
				return false;
			}
			else
				return search(s_node->right, _key);
		else if (_key == s_node->key)
		{
			cout << "the element at " << _key << " node is " << s_node->element << endl;
			return true;
		}
		else
		{
			cout << "unknown error!!!!!!!!!!!!!!!" << endl;
			return false;
		}
	}
	void printInOrder(Node* p) const
	{
		if (p->left != nullptr)
			printInOrder(p->left);
		cout << "(" << p->key << "," << p->element << ") ";
		if (p->right != nullptr)
			printInOrder(p->right);
	}
	void printPreOrder(Node* p) const
	{

		cout << "(" << p->key << "," << p->element << ") ";
		if (p->left != nullptr)
			printPreOrder(p->left);
		if (p->right != nullptr)
			printPreOrder(p->right);
	}
	void printPostOrder(Node* p) const
	{
		if (p->left != nullptr)
			printPostOrder(p->left);
		if (p->right != nullptr)
			printPostOrder(p->right);
		cout << "(" << p->key << "," << p->element << ") ";
	}
	void Release_BST(Node* p)
	{
		if (p->left != nullptr)
			Release_BST(p->left);
		if (p->right != nullptr)
			Release_BST(p->right);
		cout << "deleting (" << p->key << "," << p->element << ") at " << p << endl;
		delete p;
	}
	void CutOut(Node* p, int cut_key)
	{
		if (cut_key < p->key)
		{
			if (p->left == nullptr)
				cout << "nothing to cut !!!" << endl;
			else
				CutOut(p->left, cut_key);
		}
		else if (cut_key > p->key)
		{
			if (p->right == nullptr)
				cout << "nothing to cut !!!" << endl;
			else
				CutOut(p->right, cut_key);
		}
		else	//p is the node to be cut out
		{
			Cut(p);
		}
	}
	void Cut(Node* cut_node)
	{
		if ((cut_node->left != nullptr) && (cut_node->right == nullptr))
		{
			Node* pre_node;
			Node* catch_node;
			pre_node = find_pre(cut_node, root);
			catch_node = cut_node->left;
			delete cut_node;
			if (catch_node->key < pre_node->key)
				pre_node->left = catch_node;
			else
				pre_node->right = catch_node;
		}
		else if ((cut_node->left == nullptr) && (cut_node->right != nullptr))
		{
			Node* pre_node;
			Node* catch_node;
			pre_node = find_pre(cut_node, root);
			catch_node = cut_node->right;
			delete cut_node;
			if (catch_node->key < pre_node->key)
				pre_node->left = catch_node;
			else
				pre_node->right = catch_node;
		}
		else if ((cut_node->left != nullptr) && (cut_node->right != nullptr))
		{
			Node* pre_node;
			Node* switch_node;
			switch_node = cut_node->right;
			while (switch_node->left != nullptr)
				switch_node = switch_node->left;
			pre_node = find_pre(switch_node, root);
			if (switch_node->right != nullptr)
			{
				Node* catch_node;
				catch_node = switch_node->right;
				cut_node->element = switch_node->element;
				cut_node->key = switch_node->key;
				delete switch_node;
				if (catch_node->key < pre_node->key)
					pre_node->left = catch_node;
				else
					pre_node->right = catch_node;
			}
			else
			{
				int cut_key = switch_node->key;
				cut_node->element = switch_node->element;
				cut_node->key = switch_node->key;
				delete switch_node;
				if (cut_key < pre_node->key)
					pre_node->left = nullptr;
				else
					pre_node->right = nullptr;
			}
		}
		else
		{
			Node* pre_node;
			pre_node = find_pre(cut_node, root);
			int cut_key = cut_node->key;
			delete cut_node;
			if (cut_key < pre_node->key)
				pre_node->left = nullptr;
			else
				pre_node->right = nullptr;
		}
	}
	Node* find_pre(Node* node_check, Node* path_node) const
	{
		Node* left_path = path_node->left;
		Node* right_path = path_node->right;
		if (node_check->key == left_path->key)
			return path_node;
		else if (node_check->key == right_path->key)
			return path_node;
		else
		{
			if (node_check->key < path_node->key)
				find_pre(node_check, left_path);
			else if (node_check->key > path_node->key)
				find_pre(node_check, right_path);
			else
				cout << "find previous node failed" << endl;
		}
	}
};

#endif