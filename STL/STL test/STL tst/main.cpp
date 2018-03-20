

////////////////////////////////////////////////////////////////////
////////////////////0312 stl 3주차 첫 강의/////////////////////////
//class 복습
//---------
/////////////////////////////////////////////////////////////////////
#include <iostream>
#include "save.h"

using namespace std;

class Model {
	char * data = nullptr;			//동적할당한 메모리의 시작번지
	size_t size;					//메모리의 크기

public:
	Model() : size(0){
		cout << "default ctor " << endl;
	}

	Model(int size) : size(size) {
		data = new char[size];
		cout << "ctor size : " << size << " data : " << static_cast<void *>(data) << endl;
	}

	~Model()
	{
		cout << "dtor " << endl;
		if (data != nullptr)
			delete[] data;
	}

};
//min, max, minmax
int main()
{

	Model a;
	{
		Model b{ 1000 };
	}

	cout << "main 문 종료! " << endl;


	
}