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

        //高度
        int m_height = 1;

        T m_element;

        //左节点
        AVLnode<T>* m_left;

        //右节点
        AVLnode<T>* m_right;

        //父节点
        AVLnode<T>* m_parent;

        //节点构造函数
        AVLnode(T element, AVLnode<T>* parent) {
            m_element = element;
            m_parent = parent;
            m_left = 0;
            m_right = 0;
        }

        //判断该节点是否为叶子节点
        bool isLeaf() {
            return m_left == NULL && m_right == NULL;
        }

        //度为2
        bool hasTwoChildren() {
            return m_left != NULL && m_right != NULL;
        }

        //平衡因子
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

        //更新高度
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

        //得到更高的子树节点
        AVLnode<E>* tallerChild() {
            int leftHeight = (m_left == NULL) ? 0 : m_left->m_height;
            int rightHeight = (m_right == NULL) ? 0 : m_right->m_height;

            if (leftHeight > rightHeight) { return m_left; }
            if (leftHeight < rightHeight) { return m_right; }

            //高度一样则返回同方向的，左子树就返回左，右子树返回右
            return isLeftChild() ? m_left : m_right;
        }

        //判断是否在左子树上
        bool isLeftChild() {
            return (this->m_parent!= NULL) && (this == this->m_parent->m_left);
        }

        //判断是否为右子树
        bool isRightChild() {
            return (this->m_parent!= NULL) && (this == this->m_parent->m_right);
        }
    };

    //指向根节点的指针
    AVLnode<E>* m_root;

    //得到该节点的前驱结点
    //前驱结点：中序遍历时该节点的前一个节点
    //如果是二叉搜索树，前驱结点就是前一个比他小的节点
    AVLnode<E>* predesessor(AVLnode<E>* node) {
        //if node.left!=null前驱结点就是左子树中最大节点
        if (node == NULL)  return NULL;
        //存在左子树，前驱结点为左子树的一直right
        if (node->m_left != NULL) {
            AVLnode<E>* p = node->m_left;
            while (p->m_right != NULL) {
                p = p->m_right;
            }
            return p;
        }

        //从父节点的父节点中寻找
        //左边为空，且在父节点的左子树中
        while ((node->m_parent != NULL) && (node == node->m_parent->m_left)) {
            node = node->m_parent;
        }

        //第一种情况parent为空
        //第二种情况，节点为父节点的右子树
        return node->m_parent;
    }

    //后继节点
    AVLnode<E>* successor(AVLnode<E>* node) {
        //if node.right!=null前驱结点就是左子树中最大节点
        if (node == NULL)  return NULL;
        //存在左子树，前驱结点为左子树的一直right
        if (node->m_right != NULL) {
            AVLnode<E>* p = node->m_right;
            while (p->m_left != NULL) {
                p = p->m_left;
            }
            return p;
        }

        //从父节点的父节点中寻找
        //左边为空，且在父节点的左子树中
        while ((node->m_parent != NULL) && (node == node->m_parent->m_right)) {
            node = node->m_parent;
        }

        //第一种情况parent为空
        //第二种情况，节点为父节点的右子树
        return node->m_parent;
    }

    //传一个元素进来返回该元素对应的节点
    AVLnode<E>* node(E element) {
        AVLnode<E>* node = m_root;
        while (node != NULL) {
            if (node->m_element == element)    return node;
            if (node->m_element > element)     node = node->m_left;
            if (node->m_element < element)     node = node->m_right;
        }
        return NULL;
    }

    //删除该节点
    void remove(AVLnode<E>* node) {
        if (node == NULL)  return;
        //先分析度为2的节点
        if (node->hasTwoChildren()) {
            //找到后继节点
            AVLnode<E>* s = successor(node);

            //用后继节点的值覆盖度为2的节点的值
            node->m_element = s->m_element;
            //删除后继节点，后续删除node的度为1或0的节点
            node = s;
        }

        //度为1或0的节点
        AVLnode<E>* replacement = node->m_left != NULL ? node->m_left : node->m_right;
        if (replacement != NULL) {
            //表示node是度为1的节点

            //node->m_parent可能为NULL，根节点，所以要先对node进行判断
            if (node->m_parent == NULL) {
                m_root = replacement;
                replacement->m_parent = node->m_parent;
            }
            else if (node == node->m_parent->m_left) {//左子节点
                node->m_parent->m_left = replacement;
                replacement->m_parent = node->m_parent;
            }
            else {//右子节点
                node->m_parent->m_right = replacement;
                replacement->m_parent->m_right = node->m_parent;
            }

        
        }
        //表示node是度为0的节点
        else if (node->m_parent == NULL) {//并且node是根节点
            m_root = 0;
        }
        else {
            //叶子节点但不是根节点
            if (node == node->m_parent->m_right) {
                //叶子节点在父节点的右边
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
                // 更新高度
                updateHeight(node);
            }
            else {
                // 恢复平衡
                reBlance(node);
            }
        }
        delete temp;

    }

    //左旋转
    void rotateLeft(AVLnode<E>* grand) {
        AVLnode<E>* parent = grand->m_right;
        AVLnode<E>* child = parent->m_left;

        grand->m_right = child;
        parent->m_left = grand;

        afterRotate(grand, parent, child);
    }

    //右旋转
    void rotateRight(AVLnode<E>* grand) {
        AVLnode<E>* parent = grand->m_left;
        AVLnode<E>* child = parent->m_right;

        grand->m_left = child;
        parent->m_right = grand;

        afterRotate(grand, parent, child);
    }

    //旋转完之后的调整
    void afterRotate(AVLnode<E>* grand, AVLnode<E>* parent, AVLnode<E>* child) {
        //parent的父节点为原来grand的父节点
        parent->m_parent = grand->m_parent;

        //更改原先grand的父节点的子节点
        if (grand->isLeftChild())
        {
            grand->m_parent->m_left = parent;
        }
        else if (grand->isRightChild()) {
            grand->m_parent->m_right = parent;
        }
        else {
            //根节点
            m_root = parent;
        }

        //判断child是否为空
        //将child节点的父节点指向grand
        if (child != NULL)
        {
            child->m_parent = grand;
        }
        grand->m_parent = parent;

        updateHeight(grand);
        updateHeight(parent);
    }

    //判断节点是否平衡
    bool isBalanced(AVLnode<E>* node) {
        return (node->balanceFactor() <= 1) && (node->balanceFactor() >= -1);
    }

    //添加元素之后的调整
    void afterAdd(AVLnode<E>* node) {
        while ((node = node->m_parent) != NULL) {
            if (isBalanced(node)) {
                //更新高度
                updateHeight(node);
            }
            else {
                //恢复平衡
                reBlance(node);
                break;
            }
        }
    }


public:

    //构造函数
    AVLtree() {
        m_root = NULL;
        m_size = 0;
    }

    //树的元素个数
    int size() { return m_size; }

    //清空容器
    void clear() {
        m_size = 0;
        //层序遍历再删除
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

    //增加节点
    void add(E element) {

        //添加第一个节点
        if (m_root == NULL) {
            m_root = new AVLnode<E>(element, NULL);
            m_size++;
            return;
        }

        //添加的不是第一个节点
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
                //相等覆盖原来的element
                node->m_element = element;
                return;
            }
        }

        AVLnode<E>* newNode = new AVLnode<E>(element, parent);
        if (cmp > 0) {
            //插到父节点右边
            parent->m_right = newNode;
        }
        else {
            parent->m_left = newNode;
        }

        afterAdd(newNode);
        this->m_size++;
    }

    //删除节点,提供的是元素
    void remove(E element) {
        remove(node(element));
    }
    
    //恢复平衡
    void reBlance(AVLnode<E>* grand) {
        AVLnode<E>* parent = grand->tallerChild();
        AVLnode<E>* node = parent->tallerChild();

        //parent是左子树
        if (parent->isLeftChild()) {
            if (node->isLeftChild()) {//LL
                rotateRight(grand);

            }
            else {//LR
                rotateLeft(parent);
                rotateRight(grand);
            }
        }
        else {//parent是右子树
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

    //层序遍历
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
