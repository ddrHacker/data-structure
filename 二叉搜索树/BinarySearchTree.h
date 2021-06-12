#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#pragma once

#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;

template<typename E>
class BinarySearchTree{
private:
    int m_size;

    template<typename T>
    class Node{
    public:
        T m_element;

        //左节点
        Node<T>*m_left;

        //右节点
        Node<T>*m_right;

        //父节点
        Node<T>*m_parent;

        //节点构造函数
        Node(T element,Node<T>*parent){
            m_element=element;
            m_parent=parent;
            m_left=0;
            m_right=0;
        }

        //判断该节点是否为叶子节点
        bool isLeaf(){
            return m_left==NULL&&m_right==NULL;
        }

        //度为2
        bool hasTwoChildren(){
            return m_left!=NULL&&m_right!=NULL;
        }
    };

    //指向根节点的指针
    Node<E>*m_root;


    //前序遍历，根节点，前序访问左子树，前序访问右子树
    void preorderTraversal(Node<E>*node){
        if(node==NULL)  return;

        cout<<node->m_element<<" ";
        preorderTraversal(node->m_left);
        preorderTraversal(node->m_right);
    }

    //中序遍历左子树，根节点，中序访问右子树
    //中序遍历会导致从小到大的结果
    void inorderTraversal(Node<E>*node){
        if(node==NULL)  return;
        inorderTraversal(node->m_left);
        cout<<node->m_element<<" ";
        inorderTraversal(node->m_right);
    }

    //后序遍历
    void postorderTraversal(Node<E>*node){
        if(node==NULL)  return;
        postorderTraversal(node->m_left);

        postorderTraversal(node->m_right);

        cout<<node->m_element<<" ";
    }

    //返回某个节点位置的高度
    int height1(Node<E>*node){
        if(node==NULL)  return 0;
        //递归实现
        return max(height(node->m_left),height(node->m_right))+1;
        
    }

    //迭代实现，参考层序遍历
    //每当上一层元素访问完之后，队列的size就是下一层的元素个数
    int height2(Node<E>*node){
        if(m_root==NULL)    return 0;

        int height=0;
        //存储每一层元素的数量
        //根节点默认为1
        int levelSize=1;

        queue<Node<E>*>q;
        q.push(m_root);

        while(!q.empty()){
            Node<E>*node=q.front();
            q.pop();
            levelSize--;

            //一旦减为0，意味着这一层已经访问完了


            if(node->m_left!=NULL){
                q.push(node->m_left);
            }

            if(node->m_right!=NULL){
                q.push(node->m_right);
            }

            if(levelSize==0){
                //即将访问下一层
                levelSize=q.size();
                //已经访问完了一层
                height++;
            }
        }

        return height;
    }

    //翻转二叉树，将节点里的所有左右子树都交换，递归方法
    void invertTree1(Node<E>*node){
        if(node==NULL)  return;
        //交换节点的左右子节点
        Node<E>*temp=node->m_left;
        node->m_left=node->m_right;
        node->m_right=temp;

        invertTree1(node->m_left);
        invertTree1(node->m_right);
    }

    //层序遍历翻转二叉树
    void invertTree2(Node<E>*node){
        if(m_root==NULL)    return;
        queue<Node<E>*>q;
        q.push(m_root);

        while(!q.empty()){
            Node<E>*temp=q.front();
            q.pop();
            Node<E>*tmp=temp->m_right;
            temp->m_right=temp->m_left;
            temp->m_left=tmp;

            
            if(temp->m_left!=NULL){
                q.push(temp->m_left);
            }

            if(temp->m_right!=NULL){
                q.push(temp->m_right);
            }
        }
    }

    //得到该节点的前驱结点
    //前驱结点：中序遍历时该节点的前一个节点
    //如果是二叉搜索树，前驱结点就是前一个比他小的节点
    Node<E>*predesessor(Node<E>*node){
        //if node.left!=null前驱结点就是左子树中最大节点
        if(node==NULL)  return NULL;
        //存在左子树，前驱结点为左子树的一直right
        if(node->m_left!=NULL){
            Node<E>*p=node->m_left;
            while(p->m_right!=NULL){
                p=p->m_right;
            }
            return p;
        }

        //从父节点的父节点中寻找
        //左边为空，且在父节点的左子树中
        while((node->m_parent!=NULL)&&(node==node->m_parent->m_left)){
            node=node->m_parent;
        }

        //第一种情况parent为空
        //第二种情况，节点为父节点的右子树
        return node->m_parent;
    }

    //后继节点
    Node<E>*successor(Node<E>*node){
        //if node.right!=null前驱结点就是左子树中最大节点
        if(node==NULL)  return NULL;
        //存在左子树，前驱结点为左子树的一直right
        if(node->m_right!=NULL){
            Node<E>*p=node->m_right;
            while(p->m_left!=NULL){
                p=p->m_left;
            }
            return p;
        }

        //从父节点的父节点中寻找
        //左边为空，且在父节点的左子树中
        while((node->m_parent!=NULL)&&(node==node->m_parent->m_right)){
            node=node->m_parent;
        }

        //第一种情况parent为空
        //第二种情况，节点为父节点的右子树
        return node->m_parent;
    }

    //传一个元素进来返回该元素对应的节点
    Node<E>*node(E element){
        Node<E>*node=m_root;
        while(node!=NULL){
            if(node->m_element==element)    return node;
            if(node->m_element>element)     node=node->m_left;
            if(node->m_element<element)     node=node->m_right;
        }
        return NULL;
    }

    //删除该节点
    void remove(Node<E>*node){
        if(node==NULL)  return;
        //先分析度为2的节点
        if(node->hasTwoChildren()){
            //找到后继节点
            Node<E>*s=successor(node);

            //用后继节点的值覆盖度为2的节点的值
            node->m_element=s->m_element;
            //删除后继节点，后续删除node的度为1或0的节点
            node=s;
        }

        //度为1或0的节点
        Node<E>*replacement=node->m_left!=NULL  ?   node->m_left    :node->m_right; 
        if(replacement!=NULL){
            //表示node是度为1的节点

            //node->m_parent可能为NULL，根节点，所以要先对node进行判断
            if(node->m_parent==NULL){
                m_root=replacement;
                replacement->m_parent=node->m_parent;
                delete node;
                node=0;
            }else if(node==node->m_parent->m_left){
                node->m_parent->m_left=replacement;
                replacement->m_parent=node->m_parent;
                delete node;
                node=0;
            }else{
                node->m_parent->m_right=replacement;
                replacement->m_parent->m_right=node->m_parent;
                delete node;
                node=0;
            }

        //表示node是度为0的节点
        }else if(node->m_parent==NULL){//并且node是根节点
            delete node;
            node=0;
            m_root=0;
        }else{
            //叶子节点但不是根节点
            if(node==node->m_parent->m_right){
                //叶子节点在父节点的右边
                node->m_parent->m_right=0;
                delete node;
                node=0;
            }else{
                node->m_parent->m_left=0;
                delete node;
                node=0;
            }
        }
        m_size--;
    }
public:

    //构造函数
    BinarySearchTree(){
        m_root=NULL;            
        m_size=0;
    }

    //树的元素个数
    int size(){return m_size;}

    //清空容器
    void clear(){
        m_size=0;
        //层序遍历再删除
        queue<Node<E>*>q;
        q.push(m_root);
        while(!q.empty()){
            Node<E>*node=q.front();
            q.pop();
            if(node->m_left!=NULL){
                q.push(node->m_left);
            }
            if(node->m_right!=NULL){
                q.push(node->m_right);
            }
            delete node;
            node=0;
        }
        m_size=0;
    }

    //增加节点
    void add(E element){

        //添加第一个节点
        if(m_root==NULL){
            m_root=new Node<E>(element,NULL);
            m_size++;
          return;
        }
            
        //添加的不是第一个节点
        Node<E>*node=m_root;

        Node<E>*parent=m_root;

        int cmp=0;
        while(node!=NULL){
            parent=node;
            if(element>node->m_element){
                cmp=1;
            }else if(element<node->m_element){
                cmp=-1;
            }else{
                cmp=0;
            }

        if(cmp>0){
            node=node->m_right;
        }else if(cmp<0){
            node=node->m_left;
        }else{
            //相等覆盖原来的element
            node->m_element=element;
            return;
            }
        }
        
        if(cmp>0){
            //插到父节点右边
            parent->m_right=new Node<E>(element,parent);
        }else{
            parent->m_left=new Node<E>(element,parent);
        }
        this->m_size++;
    }

    //删除节点,提供的是元素
    void remove(E element){
        remove(node(element));
    }

    //判断是否含有该元素
    bool contains(E element){
        return (node(element)!=NULL);
    }

    //前序遍历
    void preorderTraversal(){
        this->preorderTraversal(m_root);
    }

    //中序遍历
    void inorderTraversal(){
        inorderTraversal(m_root);
    }

    //后序遍历
    void postorderTraversal(){
        postorderTraversal(m_root);
    }
    
    //层序遍历
    void levelorderTraversal(){
        if(m_root==NULL)    return;
        queue<Node<E>*>q;
        q.push(m_root);

        while(!q.empty()){
            Node<E>*node=q.front();
            q.pop();
            cout<<node->m_element<<" ";
            if(node->m_left!=NULL){
                q.push(node->m_left);
            }

            if(node->m_right!=NULL){
                q.push(node->m_right);
            }
        }
    }

    //判断二叉树高度
    int height(){
        //根节点高度到最远结点的高度
        return height2(m_root);
    }

    //判断是否为完全二叉树
    bool isComplete(){
        if(m_root==NULL)    return false;
        queue<Node<E>*>q;
        q.push(m_root);
        
        bool leaf=false;

        while(!q.empty()){
            Node<E>*node=q.front();
            q.pop();

            if(leaf&&(!node->isLeaf())){
                return false;
            }

            if(node->hasTwoChildren()){
                //左右节点都不为空，左右都入队
                q.push(node->m_left);
                q.push(node->m_right);
            }else if((node->m_right!=NULL)&&(node->m_left==NULL)){
                //左节点为空，右节点不为空
                return false;
            }else{
                //后面遍历的节点都必须是叶子节点
                //两种情况：左空右不空，左右都空
                leaf=true;
                if(node->m_left!=NULL){
                    q.push(node->m_left);
                }
            }
        }

        return true;
    }

    void invertTree(){
        invertTree1(m_root);
    }
};


#endif