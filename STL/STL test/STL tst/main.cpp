

////////////////////////////////////////////////////////////////////
////////////////////0312 stl 2���� ù ����/////////////////////////

//templet						//1����
//qsort							//2���� ù ����
//void �ǹ�						//2���� ù ����
//lambda�� ���					//2���� ù ����
//���� ����/���� ����?/ ���� ����	//2���� �ι�° ����
//���� ����¿� ���� �����غ���		//2���� �ι�° ����

// 2018. 1. STL �� 23, ȭ 56   3�� 12��   (2�� 1����)
// å�̳� ������ ���ؼ� C++, STL�� ��������
// 1. qsort ����� �����ϴ� 4��° ����
//    void�� �ǹ�
//     lambda�� ���
//---------
/////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <random>
#include <Windows.h>
#include "save.h"

using namespace std;

class Dog
{
private:
	int age;
	string name{ } ;
public:
	void setAge(int n) { age = n; }
	int getAge() const { return age; }
	string getName() const { return name; }
	friend ostream & operator<< (ostream &, const Dog);
};


ostream & operator<< (ostream & os, const Dog dog)
{
	os << "�̸� : " << dog.getName() << ", " << "���� : " << dog.getAge() << endl;
	return os;
}
int main()
{
	Dog dogs[1000];

	default_random_engine drl;								//����� �⺻ ���� ����
	uniform_int_distribution<int>uid;						//��� �������� ����
	
	for (auto & d : dogs)
	{
		d.setAge(uid(drl));									//������ int�� �ڷḦ ����ϰԵ�
	}

	//����Ʈ (������, �ڷ���, �ڷ��� ũ��, ���Լ� ������)
	//void * �� �ڷ����� ������ ��� �ڷ����� �ּҸ� ������ �� �ִ�.

	//���̷� ���� ��

	//���� ����
	//[](����)-> ��ȯ �ڷ��� {����}

	qsort(dogs, 1000, sizeof(Dog), [](const void * d1, const void * d2) -> int{
		return static_cast<const Dog *>(d1)->getAge()
			- static_cast<const Dog *>(d2)->getAge();
	});

	for (auto & d : dogs)					//�������� ����� auto d�� ����ҽ� ���縦 �����ϱ� ����
	{
		cout << d;
	}
	
	save();

	system("pause");

}



