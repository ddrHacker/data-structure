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

	//�ж������Ƿ�Ϊ��
	bool isEmpty() { return this->size == 0; }

	//���������С
	int getSize() { return size; }

	//��ȡindexλ�õĽ��
	Node<T>* getNode(int index)
	{
		Node<T>* begin = this->first;
		for (int i = 0; i < index; i++)
		{
			begin = begin->next;
		}

		return begin;
	}

	//��indexλ�ò�������
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

	//β��
	void add(T element)
	{
		add(element, this->size);
	}

	//ɾ��indexλ�õĽ��
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

	//βɾ
	void remove()
	{
		remove(this->size-1);
	}

	//�������
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

	//�ж�element��λ��
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

	//����indexλ��Ԫ��
	void set(T element, int index)
	{
		Node<T>* curr = getNode(index);
		curr->element = element;
	}

	//��ת����
	//�ǵݹ�
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

	//�ݹ鷴ת
	void reverse2(Node<T>*head)
	{
		Node<T>* newHead=0;
		newHead = reverse2(head->next);

		//��ʱhead->next��β���
		head->next->next = head;
		head->next = NULL;

		this->first = newHead;
	}
};