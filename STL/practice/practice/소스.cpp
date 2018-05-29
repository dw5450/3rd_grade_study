/////////////////////////////////////////////////////////////////////////////////////////////
//2018.04.16		STL (�� 23 , ȭ 56)					 7�� 1
//
//
// ǥ�ؿ� �´� �����̳ʿ� �ݺ��ڸ� ������
///////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>

//���� ����� ����� ������ �Ұ��Դϴ�
//#include "Model.h"							//���� ����ҽ� �߰��� ����� �ּ���
#include "save.h"
using namespace std;

class myIter {
	char * p{ nullptr };
public:
	myIter(char * p) : p{ p } {}

//�ݺ��ڰ� �ؾ� �� �⺻ ������ ���α׷��ؾ���.
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

	//�����̳ʰ� �����ϴ� �Լ�
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
	myString s{ "Hellow, world!" };			//char*, char[]�� ��ġ�ϴ� class
	myString s1 = s;

	cout << s1 << endl;						//s.operator+=(const char * s)
	s += " STL �� ����ִ�!";
	cout << s.length() << endl;
	cout << s.size() << endl;
	cout << s << endl;

	char str[40]; 
	strcpy_s(str, s.c_str());
	cout << str << endl;

	
	//for (char d : s)							//ǥ�� �����̳ʶ�� �� �ڵ忡 ������ ����� ��
	//	cout << d << ' ';
	//cout << endl;

	auto iter = find(begin(s), end(s), 'w');

	cout << typeid(iter).name() << endl;

	if (iter == s.end())
		cout << "�����ϴ�." << endl;
	else
		cout << "�ֽ��ϴ�." << endl;


	iterator_traits<myIter>::iterator_category c;
	cout << typeid(c).name() << endl;
	

	save("Ÿ���� �� �� �ְ� ������..txt");

}