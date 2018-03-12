

////////////////////////////////////////////////////////////////////
////////////////////0312 stl 2주차 첫 강의/////////////////////////

// 2018. 1. STL 월 23, 화 56   3월 12일   (2주 1일차)
// 책이나 구글을 통해서 C++, STL을 공부하자
// 1. qsort 기능을 전달하는 4번째 인자
//    void의 의미
//     lambda의 사용
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
	os << "이름 : " << dog.getName() << ", " << "나이 : " << dog.getAge() << endl;
	return os;
}
int main()
{
	Dog dogs[1000];

	default_random_engine drl;								//사용할 기본 엔진 선인
	uniform_int_distribution<int>uid;						//어떻게 분포할지 선언
	
	for (auto & d : dogs)
	{
		d.setAge(uid(drl));									//랜덤한 int형 자료를 사용하게됨
	}

	//퀵소트 (데이터, 자료형, 자료형 크기, 비교함수 포인터)
	//void * 로 자료형을 받을시 모든 자료형의 주소를 가져올 수 있다.

	//나이로 값을 비교

	//람다 람후
	//[](인자)-> 반환 자료형 {내용}

	qsort(dogs, 1000, sizeof(Dog), [](const void * d1, const void * d2) -> int{
		return static_cast<const Dog *>(d1)->getAge()
			- static_cast<const Dog *>(d2)->getAge();
	});

	for (auto & d : dogs)					//참조형을 써야함 auto d를 사용할시 복사를 실행하기 때문
	{
		cout << d;
	}
	
	save();

	system("pause");

}



