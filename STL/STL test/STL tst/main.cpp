#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include "save.h"
#include <algorithm>
#include <chrono>


using namespace std;

std::uniform_int_distribution<> uid(1, 1000);
std::default_random_engine dre;

class Dog
{
	int age;
	char name[10] = "unknown";

public:
	Dog()
	{
		age = uid(dre);
	}
	int getAge() const { return age; }

};


int main()
{
	////���� 100000���� ���̳ʸ��� �����غ���!
	//int dog_num = 100000;
	//std::string dog_100000 = "�� 100000����";
	//Dog * dogs = new Dog[dog_num];
	//std::ofstream out(dog_100000, std::ios::binary);

	//delete[] dogs;
	

	//�� �� 100000������ �ҷ��� ����!


	//int dog_num = 10000;
	//std::string dog_100000 = "�� 100000����";
	//Dog dogs[10000];
	//std::ifstream in(dog_100000, std::ios::binary);
	//in.read((char *)dogs, sizeof(Dog) * dog_num);


	/*auto cur_time = chrono::high_resolution_clock::now();

	auto elapse_time = chrono::high_resolution_clock::now() - cur_time;

	cout << chrono::duration<double, std::chrono::milliseconds::period>(elapse_time).count() << endl;*/


	auto begin = std::chrono::high_resolution_clock::now();

	// ������ �ڵ�� ���⿡
	auto elapsedTime = std::chrono::high_resolution_clock::now() - begin;
	std::cout << std::chrono::duration<double>(elapsedTime).count() << "�� ���" << std::endl;

	//��Ʈ �غ���!

	/*sort(begin(dogs), end(dogs),
		[](const Dog & a, const Dog & b) {
		return a.getAge() < b.getAge();
	});
	for (int i = 0; i < 10; i++)
		std::cout << dogs[i].getAge() << std::endl;

	delete[] dogs;*/

}