#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#pragma once

#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;

template<typename E>
class AVLtree{
private:
    int m_size;

    template<typename T>
    class AVLnode{
    public:
        T m_element;

        //��ڵ�
        AVLnode<T>*m_left;

        //�ҽڵ�
        AVLnode<T>*m_right;

        //���ڵ�
        AVLnode<T>*m_parent;

        //�ڵ㹹�캯��
        AVLnode(T element,AVLnode<T>*parent){
            m_element=element;
            m_parent=parent;
            m_left=0;
            m_right=0;
        }

        //�жϸýڵ��Ƿ�ΪҶ�ӽڵ�
        bool isLeaf(){
            return m_left==NULL&&m_right==NULL;
        }

        //��Ϊ2
        bool hasTwoChildren(){
            return m_left!=NULL&&m_right!=NULL;
        }
    };

    //ָ����ڵ��ָ��
    AVLnode<E>*m_root;


    //ǰ����������ڵ㣬ǰ�������������ǰ�����������
    void preorderTraversal(AVLnode<E>*node){
        if(node==NULL)  return;

        cout<<node->m_element<<" ";
        preorderTraversal(node->m_left);
        preorderTraversal(node->m_right);
    }

    //������������������ڵ㣬�������������
    //��������ᵼ�´�С����Ľ��
    void inorderTraversal(AVLnode<E>*node){
        if(node==NULL)  return;
        inorderTraversal(node->m_left);
        cout<<node->m_element<<" ";
        inorderTraversal(node->m_right);
    }

    //�������
    void postorderTraversal(AVLnode<E>*node){
        if(node==NULL)  return;
        postorderTraversal(node->m_left);

        postorderTraversal(node->m_right);

        cout<<node->m_element<<" ";
    }

    //����ĳ���ڵ�λ�õĸ߶�
    int height1(AVLnode<E>*node){
        if(node==NULL)  return 0;
        //�ݹ�ʵ��
        return max(height(node->m_left),height(node->m_right))+1;

    }

    //����ʵ�֣��ο��������
    //ÿ����һ��Ԫ�ط�����֮�󣬶��е�size������һ���Ԫ�ظ���
    int height2(AVLnode<E>*node){
        if(m_root==NULL)    return 0;

        int height=0;
        //�洢ÿһ��Ԫ�ص�����
        //���ڵ�Ĭ��Ϊ1
        int levelSize=1;

        queue<AVLnode<E>*>q;
        q.push(m_root);

        while(!q.empty()){
            AVLnode<E>*node=q.front();
            q.pop();
            levelSize--;

            //һ����Ϊ0����ζ����һ���Ѿ���������


            if(node->m_left!=NULL){
                q.push(node->m_left);
            }

            if(node->m_right!=NULL){
                q.push(node->m_right);
            }

            if(levelSize==0){
                //����������һ��
                levelSize=q.size();
                //�Ѿ���������һ��
                height++;
            }
        }

        return height;
    }

    //��ת�����������ڵ�������������������������ݹ鷽��
    void invertTree1(AVLnode<E>*node){
        if(node==NULL)  return;
        //�����ڵ�������ӽڵ�
        AVLnode<E>*temp=node->m_left;
        node->m_left=node->m_right;
        node->m_right=temp;

        invertTree1(node->m_left);
        invertTree1(node->m_right);
    }

    //���������ת������
    void invertTree2(AVLnode<E>*node){
        if(m_root==NULL)    return;
        queue<AVLnode<E>*>q;
        q.push(m_root);

        while(!q.empty()){
            AVLnode<E>*temp=q.front();
            q.pop();
            AVLnode<E>*tmp=temp->m_right;
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

    //�õ��ýڵ��ǰ�����
    //ǰ����㣺�������ʱ�ýڵ��ǰһ���ڵ�
    //����Ƕ�����������ǰ��������ǰһ������С�Ľڵ�
    AVLnode<E>*predesessor(AVLnode<E>*node){
        //if node.left!=nullǰ�������������������ڵ�
        if(node==NULL)  return NULL;
        //������������ǰ�����Ϊ��������һֱright
        if(node->m_left!=NULL){
            AVLnode<E>*p=node->m_left;
            while(p->m_right!=NULL){
                p=p->m_right;
            }
            return p;
        }

        //�Ӹ��ڵ�ĸ��ڵ���Ѱ��
        //���Ϊ�գ����ڸ��ڵ����������
        while((node->m_parent!=NULL)&&(node==node->m_parent->m_left)){
            node=node->m_parent;
        }

        //��һ�����parentΪ��
        //�ڶ���������ڵ�Ϊ���ڵ��������
        return node->m_parent;
    }

    //��̽ڵ�
    AVLnode<E>*successor(AVLnode<E>*node){
        //if node.right!=nullǰ�������������������ڵ�
        if(node==NULL)  return NULL;
        //������������ǰ�����Ϊ��������һֱright
        if(node->m_right!=NULL){
            AVLnode<E>*p=node->m_right;
            while(p->m_left!=NULL){
                p=p->m_left;
            }
            return p;
        }

        //�Ӹ��ڵ�ĸ��ڵ���Ѱ��
        //���Ϊ�գ����ڸ��ڵ����������
        while((node->m_parent!=NULL)&&(node==node->m_parent->m_right)){
            node=node->m_parent;
        }

        //��һ�����parentΪ��
        //�ڶ���������ڵ�Ϊ���ڵ��������
        return node->m_parent;
    }

    //��һ��Ԫ�ؽ������ظ�Ԫ�ض�Ӧ�Ľڵ�
    AVLnode<E>*node(E element){
        AVLnode<E>*node=m_root;
        while(node!=NULL){
            if(node->m_element==element)    return node;
            if(node->m_element>element)     node=node->m_left;
            if(node->m_element<element)     node=node->m_right;
        }
        return NULL;
    }

    //ɾ���ýڵ�
    void remove(AVLnode<E>*node){
        if(node==NULL)  return;
        //�ȷ�����Ϊ2�Ľڵ�
        if(node->hasTwoChildren()){
            //�ҵ���̽ڵ�
            AVLnode<E>*s=successor(node);

            //�ú�̽ڵ��ֵ���Ƕ�Ϊ2�Ľڵ��ֵ
            node->m_element=s->m_element;
            //ɾ����̽ڵ㣬����ɾ��node�Ķ�Ϊ1��0�Ľڵ�
            node=s;
        }

        //��Ϊ1��0�Ľڵ�
        AVLnode<E>*replacement=node->m_left!=NULL  ?   node->m_left    :node->m_right;
        if(replacement!=NULL){
            //��ʾnode�Ƕ�Ϊ1�Ľڵ�

            //node->m_parent����ΪNULL�����ڵ㣬����Ҫ�ȶ�node�����ж�
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

        //��ʾnode�Ƕ�Ϊ0�Ľڵ�
        }else if(node->m_parent==NULL){//����node�Ǹ��ڵ�
            delete node;
            node=0;
            m_root=0;
        }else{
            //Ҷ�ӽڵ㵫���Ǹ��ڵ�
            if(node==node->m_parent->m_right){
                //Ҷ�ӽڵ��ڸ��ڵ���ұ�
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

    //���캯��
    AVLTree(){
        m_root=NULL;
        m_size=0;
    }

    //����Ԫ�ظ���
    int size(){return m_size;}

    //�������
    void clear(){
        m_size=0;
        //���������ɾ��
        queue<AVLnode<E>*>q;
        q.push(m_root);
        while(!q.empty()){
            AVLnode<E>*node=q.front();
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

    //���ӽڵ�
    void add(E element){

        //��ӵ�һ���ڵ�
        if(m_root==NULL){
            m_root=new AVLnode<E>(element,NULL);
            m_size++;
          return;
        }

        //��ӵĲ��ǵ�һ���ڵ�
        AVLnode<E>*node=m_root;

        AVLnode<E>*parent=m_root;

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
            //��ȸ���ԭ����element
            node->m_element=element;
            return;
            }
        }

        if(cmp>0){
            //�嵽���ڵ��ұ�
            parent->m_right=new AVLnode<E>(element,parent);
        }else{
            parent->m_left=new AVLnode<E>(element,parent);
        }
        this->m_size++;
    }

    //ɾ���ڵ�,�ṩ����Ԫ��
    void remove(E element){
        remove(node(element));
    }

    //�ж��Ƿ��и�Ԫ��
    bool contains(E element){
        return (node(element)!=NULL);
    }

    //ǰ�����
    void preorderTraversal(){
        this->preorderTraversal(m_root);
    }

    //�������
    void inorderTraversal(){
        inorderTraversal(m_root);
    }

    //�������
    void postorderTraversal(){
        postorderTraversal(m_root);
    }

    //�������
    void levelorderTraversal(){
        if(m_root==NULL)    return;
        queue<AVLnode<E>*>q;
        q.push(m_root);

        while(!q.empty()){
            AVLnode<E>*node=q.front();
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

    //�ж϶������߶�
    int height(){
        //���ڵ�߶ȵ���Զ���ĸ߶�
        return height2(m_root);
    }

    //�ж��Ƿ�Ϊ��ȫ������
    bool isComplete(){
        if(m_root==NULL)    return false;
        queue<AVLnode<E>*>q;
        q.push(m_root);

        bool leaf=false;

        while(!q.empty()){
            AVLnode<E>*node=q.front();
            q.pop();

            if(leaf&&(!node->isLeaf())){
                return false;
            }

            if(node->hasTwoChildren()){
                //���ҽڵ㶼��Ϊ�գ����Ҷ����
                q.push(node->m_left);
                q.push(node->m_right);
            }else if((node->m_right!=NULL)&&(node->m_left==NULL)){
                //��ڵ�Ϊ�գ��ҽڵ㲻Ϊ��
                return false;
            }else{
                //��������Ľڵ㶼������Ҷ�ӽڵ�
                //�������������Ҳ��գ����Ҷ���
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
