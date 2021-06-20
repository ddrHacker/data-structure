#include"AVLtree.h"
#include<iostream>
using namespace std;

int main()
{
	AVLtree<int>avl;
	avl.add(1);
	avl.add(2);
	avl.add(3);
	avl.add(4);
	avl.add(5);
	avl.levelorderTraversal();

	cout << endl;
	avl.remove(5);
	avl.levelorderTraversal();
	return 0;
}