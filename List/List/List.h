#pragma once
#include<iostream>
using namespace std;

template<typename T>
class List
{
private:
	
	template<typename T>
	class Node
	{
	public:
		T element;
		Node<T>* next;

		Node<T>(T num):element(num),next(0){}

		Node<T>(T num,Node<T>*address):element(num),next(address){}
	};

	int size;
	Node<T>* first;

public:
	List<T>() :size(0), first(0){}

	//判断容器是否为空
	bool isEmpty() { return this->size == 0; }

	//获得容器大小
	int getSize() { return size; }

	//获取index位置的结点
	Node<T>* getNode(int index)
	{
		Node<T>* begin = this->first;
		for (int i = 0; i < index; i++)
		{
			begin = begin->next;
		}

		return begin;
	}

	//在index位置插入数据
	void add(T element, int index)
	{
		if (index == 0)
		{
			this->first = new Node<T>(element,first);
		}

		else if(index>0)
		{
			Node<T>* prev = getNode(index - 1);
			prev->next = new Node<T>(element, prev->next);
		}
		this->size++;
	}

	//尾插
	void add(T element)
	{
		add(element, this->size);
	}

	//删除index位置的结点
	void remove(int index)
	{
		if (index == 0)
		{
			Node<T>* temp = first;
			first->next = first->next->next;
			delete temp;
		}

		if (index > 0)
		{
			Node<T>* prev = getNode(index - 1);
			Node<T>* curr = prev->next;
			prev->next = curr->next;
			delete curr;
		}
		this->size--;
	}

	//尾删
	void remove()
	{
		remove(this->size-1);
	}

	//清空容器
	void clear()
	{
		Node<T>* curr = this->first->next;
		delete first;
		while (curr != NULL)
		{
			Node<T>* tmp = curr;
			curr = tmp->next;
			delete tmp;
		}
		this->size = 0;
	}

	//判断element的位置
	int getPos(T element)
	{
		Node<T>* begin = this->first;
		int count = 0;
		for (int i = 0; i < size; i++)
		{
			if (element == begin->element)
				return count;
			else
				count++;
		}
		return -1;
	}

	//更改index位置元素
	void set(T element, int index)
	{
		Node<T>* curr = getNode(index);
		curr->element = element;
	}

	//反转链表
	//非递归
	void reverse1()
	{
		Node<T>* Next = this->first->next;
		this->first->next = NULL;
		Node<T>* curr = first;

		for (int i = 0; i < this->size - 1; i++)
		{
			first = Next;
			Next = Next->next;
			first->next = curr;
			curr = first;
		}
	}

	//递归反转
	void reverse2(Node<T>*head)
	{
		Node<T>* newHead=0;
		newHead = reverse2(head->next);

		//此时head->next是尾结点
		head->next->next = head;
		head->next = NULL;

		this->first = newHead;
	}
};