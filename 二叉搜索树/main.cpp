#include<iostream>
#include"BinarySearchTree.h"
using namespace std;
//任意一个节点的值都大于其左子树所有节点的值
//任意一个节点的值都小于其右子树所有节点的值
int main()
{
    BinarySearchTree<int>*bst=new BinarySearchTree<int>();
    int arr[]={7,4,9,2,5,8,11,3,10};
    int len=sizeof(arr)/sizeof(arr[0]);
    for(int i=0;i<len;i++){
        bst->add(arr[i]);
    }

    bst->levelorderTraversal();
    bst->clear();
    cout<<bst->height();
    /*
    cout<<"未翻转前的层序遍历："<<endl;
    bst->levelorderTraversal();
    cout<<endl;
    //cout<<"the height of the binary search tree is: "<<bst->height()<<endl;
    //cout<<"whether the tree is a complete binary tree or not: "<<bst->isComplete()<<endl;

    cout<<"翻转后的层序遍历："<<endl;
    bst->invertTree();
    bst->levelorderTraversal();
    cout<<endl;
    */
    return 0;
}