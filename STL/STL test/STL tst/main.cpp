

////////////////////////////////////////////////////////////////////
////////////////////0312 stl 3���� ù ����/////////////////////////
//class ����
//---------
/////////////////////////////////////////////////////////////////////
#include <iostream>
#include "save.h"

using namespace std;

class Model {
	char * data = nullptr;			//�����Ҵ��� �޸��� ���۹���
	size_t size;					//�޸��� ũ��

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

	cout << "main �� ����! " << endl;


	
}