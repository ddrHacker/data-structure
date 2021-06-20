#include"AVLtree.h"
#include<iostream>
using namespace std;

int main()
{
    AVLtree<int>avl;
    avl.add(10);
    avl.add(5);
    avl.add(7);
    avl.add(6);
    avl.add(8);
    avl.add(13);
    avl.add(20);
    avl.add(9);

    avl.levelorderTraversal();

    return 0;
}
