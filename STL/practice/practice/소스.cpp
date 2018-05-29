/////////////////////////////////////////////////////////////////////////////////////////////
//2018.04.16		STL (�� 23 , ȭ 56)					 7�� 1
//
//
// ǥ�ؿ� �´� �����̳ʿ� �ݺ��ڸ� ������
///////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>
#include <iterator>

//���� ����� ����� ������ �Ұ��Դϴ�
//#include "Model.h"							//���� ����ҽ� �߰��� ����� �ּ���
#include "save.h"
using namespace std;


template<class InIter, class Call>
bool my_all_of(InIter b, InIter e, Call f)
{
	if (b == e)
		return true;


	while ( b != e){
		if ( !f(*b) )
			return false;
		++b;
	}

	return true;
}

int main()
{
	int a[]{ 1, 4, 6, 8, 10 };
	//��� ¦������ �˻��Ͻÿ�.

	bool result = my_all_of(begin(a), end(a), [](int n)
	{
		return !(n & 1);
	});

	if (result == true)
	{
		cout << " ��� ¦���Դϴ�" << endl;
	}
	else {
		cout << "Ȧ���� �����մϴ�." << endl;
	}
}