/////////////////////////////////////////////////////////////////////////////////////////////
//2018.04.16		STL (월 23 , 화 56)					 7주 1
//
//
// 표준에 맞는 컨테이너와 반복자를 만들어보자
///////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>

//다음 헤더는 실행시 지워야 할것입니다
//#include "Model.h"							//모델을 사용할시 추가후 사용해 주세요
#include "save.h"
using namespace std;

class myIter {
	char * p{ nullptr };
public:
	myIter(char * p) : p{ p } {}

//반복자가 해야 할 기본 동작을 프로그램해야함.
// *, ==, =, ++
	char operator*() { return *p; }
	bool operator==(const myIter & rhs) const {return p == rhs.p;}
	bool operator!=(const myIter & rhs) const { return p != rhs.p; }
	myIter& operator=(const myIter & rhs) { p = rhs.p; return *this; }
	myIter & operator++() { 
		++p;
	return *this;
	}
	myIter operator++(int) {
		myIter temp = *this;
		++p;
		return temp;
	}


};

class myString {
	int len{ 0 };
	char * p{ nullptr };
public:
	myString() {};
	~myString() {
		if (p) delete [] p;
	}
	myString(const char *);
	myString(const myString &);

	myString & operator=(const myString &);

	void operator+=(const char * );

	friend ostream & operator<< (ostream & os, const myString &);

	//컨테이너가 제공하는 함수
	int length() const { return len; }
	int size() const { return len; }
	char * c_str() const { return p; }
	myIter begin() {
		return myIter(p);
	};
	myIter end() {
		return myIter(p + len);
	};

};

myString::myString(const char * str)
{
	len = strlen(str);
	p = new char[strlen(str) + 1];
	strcpy_s(p, strlen(str) + 1, str);
}

myString::myString(const myString & other)
{
	*this = other;
}

myString & myString::operator=(const myString & other)
{
	delete[] p;
	len = other.len;
	p = new char[len + 1];
	strcpy_s(p, len + 1, other.p);

	return *this;
}

void myString::operator+=(const char * s)
{
	len += strlen(s);
	strcat_s(p, len + 1, s);
}

ostream & operator<< (ostream & os, const myString & p)
{
	os << p.p;
	return os;
}






template <class Iter, class Value>
Iter myFind(Iter beg, Iter end, Value val)
{
	while (beg != end) {
		if (*beg == val)
			return beg;
		++beg
	}
	return beg;
}







int main()
{
	myString s{ "Hellow, world!" };			//char*, char[]를 대치하는 class
	myString s1 = s;

	cout << s1 << endl;						//s.operator+=(const char * s)
	s += " STL 참 재미있다!";
	cout << s.length() << endl;
	cout << s.size() << endl;
	cout << s << endl;

	char str[40]; 
	strcpy_s(str, s.c_str());
	cout << str << endl;

	
	//for (char d : s)							//표준 컨테이너라면 이 코드에 문제가 없어야 함
	//	cout << d << ' ';
	//cout << endl;

	auto iter = find(begin(s), end(s), 'w');

	cout << typeid(iter).name() << endl;

	if (iter == s.end())
		cout << "없습니다." << endl;
	else
		cout << "있습니다." << endl;


	iterator_traits<myIter>::iterator_category c;
	cout << typeid(c).name() << endl;
	

	save("타입을 알 수 있게 해주자..txt");

}