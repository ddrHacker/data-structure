#include"List.h"
#include<iostream>
using namespace std;
class Person
{
public:
	string m_name;
	int m_age;
	Person(string name,int age):m_name(name),m_age(age){}
};

void print(List<Person>& tmp)
{
	for (int i = 0; i < tmp.getSize(); i++)
	{
		cout << "姓名:" << (tmp.getNode(i))->element.m_name << " " << (tmp.getNode(i))->element.m_age << endl;
	}
}

void test01()
{
	List<Person> l;
	l.add(Person("张三", 10));
	l.add(Person("李四", 20));
	print(l);
	cout << endl << "-----------------------------------------------------" << endl;

	l.reverse1();
	print(l);
}

void test02()
{
	List<int>l;
	for (int i = 1; i < 12; i++)
	{
		l.add(i);
	}
	l.remove();
	cout << l.getSize() << endl;

	l.clear();
	cout << l.getSize() << endl;
}

int main()
{
	//test01();
	test02();
	return 0;
}