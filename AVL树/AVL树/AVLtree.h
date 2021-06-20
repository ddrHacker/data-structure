#pragma once
#include<iostream>
#include<queue>
using namespace std;

template<typename E>
class AVLtree {
private:
    int m_size;

    template<typename T>
    class AVLnode {
    public:

        //�߶�
        int m_height = 1;

        T m_element;

        //��ڵ�
        AVLnode<T>* m_left;

        //�ҽڵ�
        AVLnode<T>* m_right;

        //���ڵ�
        AVLnode<T>* m_parent;

        //�ڵ㹹�캯��
        AVLnode(T element, AVLnode<T>* parent) {
            m_element = element;
            m_parent = parent;
            m_left = 0;
            m_right = 0;
        }

        //�жϸýڵ��Ƿ�ΪҶ�ӽڵ�
        bool isLeaf() {
            return m_left == NULL && m_right == NULL;
        }

        //��Ϊ2
        bool hasTwoChildren() {
            return m_left != NULL && m_right != NULL;
        }

        //ƽ������
        int balanceFactor() {
            int leftHeight = 0;
            int rightHeight = 0;
            if (m_left == NULL)    leftHeight = 0;
            else {
                leftHeight = m_left->m_height;
            }

            if (m_right == NULL)    rightHeight = 0;
            else {
                rightHeight = m_right->m_height;
            }
            return leftHeight - rightHeight;
        }

        //���¸߶�
        void updateHeight() {
            int leftHeight = (m_left == NULL) ? 0 : m_left->m_height;
            int rightHeight = (m_right == NULL) ? 0 : m_right->m_height;
            if (leftHeight >= rightHeight) {
                this->m_height = leftHeight + 1;
            }
            else{
                this->m_height = rightHeight + 1;
            }
        }

        //�õ����ߵ������ڵ�
        AVLnode<E>* tallerChild() {
            int leftHeight = (m_left == NULL) ? 0 : m_left->m_height;
            int rightHeight = (m_right == NULL) ? 0 : m_right->m_height;

            if (leftHeight > rightHeight) { return m_left; }
            if (leftHeight < rightHeight) { return m_right; }

            //�߶�һ���򷵻�ͬ����ģ��������ͷ�����������������
            return isLeftChild() ? m_left : m_right;
        }

        //�ж��Ƿ�����������
        bool isLeftChild() {
            return (this->m_parent!= NULL) && (this == this->m_parent->m_left);
        }

        //�ж��Ƿ�Ϊ������
        bool isRightChild() {
            return (this->m_parent!= NULL) && (this == this->m_parent->m_right);
        }
    };

    //ָ����ڵ��ָ��
    AVLnode<E>* m_root;

    //�õ��ýڵ��ǰ�����
    //ǰ����㣺�������ʱ�ýڵ��ǰһ���ڵ�
    //����Ƕ�����������ǰ��������ǰһ������С�Ľڵ�
    AVLnode<E>* predesessor(AVLnode<E>* node) {
        //if node.left!=nullǰ�������������������ڵ�
        if (node == NULL)  return NULL;
        //������������ǰ�����Ϊ��������һֱright
        if (node->m_left != NULL) {
            AVLnode<E>* p = node->m_left;
            while (p->m_right != NULL) {
                p = p->m_right;
            }
            return p;
        }

        //�Ӹ��ڵ�ĸ��ڵ���Ѱ��
        //���Ϊ�գ����ڸ��ڵ����������
        while ((node->m_parent != NULL) && (node == node->m_parent->m_left)) {
            node = node->m_parent;
        }

        //��һ�����parentΪ��
        //�ڶ���������ڵ�Ϊ���ڵ��������
        return node->m_parent;
    }

    //��̽ڵ�
    AVLnode<E>* successor(AVLnode<E>* node) {
        //if node.right!=nullǰ�������������������ڵ�
        if (node == NULL)  return NULL;
        //������������ǰ�����Ϊ��������һֱright
        if (node->m_right != NULL) {
            AVLnode<E>* p = node->m_right;
            while (p->m_left != NULL) {
                p = p->m_left;
            }
            return p;
        }

        //�Ӹ��ڵ�ĸ��ڵ���Ѱ��
        //���Ϊ�գ����ڸ��ڵ����������
        while ((node->m_parent != NULL) && (node == node->m_parent->m_right)) {
            node = node->m_parent;
        }

        //��һ�����parentΪ��
        //�ڶ���������ڵ�Ϊ���ڵ��������
        return node->m_parent;
    }

    //��һ��Ԫ�ؽ������ظ�Ԫ�ض�Ӧ�Ľڵ�
    AVLnode<E>* node(E element) {
        AVLnode<E>* node = m_root;
        while (node != NULL) {
            if (node->m_element == element)    return node;
            if (node->m_element > element)     node = node->m_left;
            if (node->m_element < element)     node = node->m_right;
        }
        return NULL;
    }

    //ɾ���ýڵ�
    void remove(AVLnode<E>* node) {
        if (node == NULL)  return;
        //�ȷ�����Ϊ2�Ľڵ�
        if (node->hasTwoChildren()) {
            //�ҵ���̽ڵ�
            AVLnode<E>* s = successor(node);

            //�ú�̽ڵ��ֵ���Ƕ�Ϊ2�Ľڵ��ֵ
            node->m_element = s->m_element;
            //ɾ����̽ڵ㣬����ɾ��node�Ķ�Ϊ1��0�Ľڵ�
            node = s;
        }

        //��Ϊ1��0�Ľڵ�
        AVLnode<E>* replacement = node->m_left != NULL ? node->m_left : node->m_right;
        if (replacement != NULL) {
            //��ʾnode�Ƕ�Ϊ1�Ľڵ�

            //node->m_parent����ΪNULL�����ڵ㣬����Ҫ�ȶ�node�����ж�
            if (node->m_parent == NULL) {
                m_root = replacement;
                replacement->m_parent = node->m_parent;
            }
            else if (node == node->m_parent->m_left) {//���ӽڵ�
                node->m_parent->m_left = replacement;
                replacement->m_parent = node->m_parent;
            }
            else {//���ӽڵ�
                node->m_parent->m_right = replacement;
                replacement->m_parent->m_right = node->m_parent;
            }

        
        }
        //��ʾnode�Ƕ�Ϊ0�Ľڵ�
        else if (node->m_parent == NULL) {//����node�Ǹ��ڵ�
            m_root = 0;
        }
        else {
            //Ҷ�ӽڵ㵫���Ǹ��ڵ�
            if (node == node->m_parent->m_right) {
                //Ҷ�ӽڵ��ڸ��ڵ���ұ�
                node->m_parent->m_right = 0;
            }
            else {
                node->m_parent->m_left = 0;
            }
        }
        afterRemove(node);
        m_size--;
    }

    void afterRemove(AVLnode<E>* node) {
        AVLnode<E>* temp = node;
        while ((node = node->m_parent) != NULL) {
            if (isBalanced(node)) {
                // ���¸߶�
                updateHeight(node);
            }
            else {
                // �ָ�ƽ��
                reBlance(node);
            }
        }
        delete temp;

    }

    //����ת
    void rotateLeft(AVLnode<E>* grand) {
        AVLnode<E>* parent = grand->m_right;
        AVLnode<E>* child = parent->m_left;

        grand->m_right = child;
        parent->m_left = grand;

        afterRotate(grand, parent, child);
    }

    //����ת
    void rotateRight(AVLnode<E>* grand) {
        AVLnode<E>* parent = grand->m_left;
        AVLnode<E>* child = parent->m_right;

        grand->m_left = child;
        parent->m_right = grand;

        afterRotate(grand, parent, child);
    }

    //��ת��֮��ĵ���
    void afterRotate(AVLnode<E>* grand, AVLnode<E>* parent, AVLnode<E>* child) {
        //parent�ĸ��ڵ�Ϊԭ��grand�ĸ��ڵ�
        parent->m_parent = grand->m_parent;

        //����ԭ��grand�ĸ��ڵ���ӽڵ�
        if (grand->isLeftChild())
        {
            grand->m_parent->m_left = parent;
        }
        else if (grand->isRightChild()) {
            grand->m_parent->m_right = parent;
        }
        else {
            //���ڵ�
            m_root = parent;
        }

        //�ж�child�Ƿ�Ϊ��
        //��child�ڵ�ĸ��ڵ�ָ��grand
        if (child != NULL)
        {
            child->m_parent = grand;
        }
        grand->m_parent = parent;

        updateHeight(grand);
        updateHeight(parent);
    }

    //�жϽڵ��Ƿ�ƽ��
    bool isBalanced(AVLnode<E>* node) {
        return (node->balanceFactor() <= 1) && (node->balanceFactor() >= -1);
    }

    //���Ԫ��֮��ĵ���
    void afterAdd(AVLnode<E>* node) {
        while ((node = node->m_parent) != NULL) {
            if (isBalanced(node)) {
                //���¸߶�
                updateHeight(node);
            }
            else {
                //�ָ�ƽ��
                reBlance(node);
                break;
            }
        }
    }


public:

    //���캯��
    AVLtree() {
        m_root = NULL;
        m_size = 0;
    }

    //����Ԫ�ظ���
    int size() { return m_size; }

    //�������
    void clear() {
        m_size = 0;
        //���������ɾ��
        queue<AVLnode<E>*>q;
        q.push(m_root);
        while (!q.empty()) {
            AVLnode<E>* node = q.front();
            q.pop();
            if (node->m_left != NULL) {
                q.push(node->m_left);
            }
            if (node->m_right != NULL) {
                q.push(node->m_right);
            }
            delete node;
            node = 0;
        }
        m_size = 0;
    }

    //���ӽڵ�
    void add(E element) {

        //��ӵ�һ���ڵ�
        if (m_root == NULL) {
            m_root = new AVLnode<E>(element, NULL);
            m_size++;
            return;
        }

        //��ӵĲ��ǵ�һ���ڵ�
        AVLnode<E>* node = m_root;

        AVLnode<E>* parent = m_root;

        int cmp = 0;
        while (node != NULL) {
            parent = node;
            if (element > node->m_element) {
                cmp = 1;
            }
            else if (element < node->m_element) {
                cmp = -1;
            }
            else {
                cmp = 0;
            }

            if (cmp > 0) {
                node = node->m_right;
            }
            else if (cmp < 0) {
                node = node->m_left;
            }
            else {
                //��ȸ���ԭ����element
                node->m_element = element;
                return;
            }
        }

        AVLnode<E>* newNode = new AVLnode<E>(element, parent);
        if (cmp > 0) {
            //�嵽���ڵ��ұ�
            parent->m_right = newNode;
        }
        else {
            parent->m_left = newNode;
        }

        afterAdd(newNode);
        this->m_size++;
    }

    //ɾ���ڵ�,�ṩ����Ԫ��
    void remove(E element) {
        remove(node(element));
    }
    
    //�ָ�ƽ��
    void reBlance(AVLnode<E>* grand) {
        AVLnode<E>* parent = grand->tallerChild();
        AVLnode<E>* node = parent->tallerChild();

        //parent��������
        if (parent->isLeftChild()) {
            if (node->isLeftChild()) {//LL
                rotateRight(grand);

            }
            else {//LR
                rotateLeft(parent);
                rotateRight(grand);
            }
        }
        else {//parent��������
            if (node->isLeftChild()) {//RL
                rotateRight(parent);
                rotateLeft(grand);
            }
            else {//RR
                rotateLeft(grand);
            }
        }
    }

    void updateHeight(AVLnode<E>* node) {
        node->updateHeight();
    }

    //�������
    void levelorderTraversal() {
        if (this->m_root == NULL)  return;
        queue<AVLnode<E>*>q;
        q.push(m_root);
        while (!q.empty()) {
            AVLnode<E>* temp = q.front();
            q.pop();
            cout << temp->m_element << " ";

            if (temp->m_left != NULL) {
                q.push(temp->m_left);
            }

            if (temp->m_right != NULL) {
                q.push(temp->m_right);
            }
        }

    }
};
