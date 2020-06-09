#include <iostream>
#include "BST.h"

using namespace std;

int main()
{
	
	BST bst;
	
	bst.insert(7, 'G');
	bst.insert(5, 'E');
	bst.insert(2, 'B');
	bst.insert(9, 'I');
	bst.insert(10, 'J');
	bst.insert(3, 'C');
	bst.insert(6, 'F');
	bst.insert(8, 'H');
	bst.insert(1, 'A');

	bst.printInOrder();
	cout << endl;
	bst.printPreOrder();
	cout << endl;
	bst.printPostOrder();
	cout << endl;

	bst.CutOut(9);

	bst.printInOrder();
	cout << endl;
	bst.printPreOrder();
	cout << endl;
	bst.printPostOrder();
	cout << endl;
	
	return 0;
}