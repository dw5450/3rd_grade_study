/////////////////////////////////////////////////////////////////////////////////////////////
//2018.04.16		STL (�� 23 , ȭ 56)					 7�� 1
//
// 7�� �ݺ���

//
///////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iterator>
#include <stack>
#include <fstream>
//���� ����� ����� ������ �Ұ��Դϴ�
#include "Model.h"							//���� ����ҽ� �߰��� ����� �ּ���
#include "save.h"
#include "funcSpeedCheck.h"
using namespace std;

//�ݺ���(��� ������ �ݺ��ڰ� ����)��� �����ؾ� �ϴ� ����
// *	: ������(dereferencing)
//==	: �� (comaprision)
//=		: �Ҵ� (assignment)

//�ݺ����� ���� (Catergory)
//����¹ݺ���
//�����ݺ���++;
//�������ݺ���(����� �ݺ���) ++, --;
//�����ݺ��� +=, -=;
class MyHash {
	public:
		size_t operator()(const Model & a) const {
			hash<int> hashVal;
			
			return hashVal(a.getSize());

		}

};
int main()
{
	//	�ҽ�.cpp�� �а� ���
	//	������� �ݺ��ڸ� ����ؼ� �ۼ��� ���ϴ�.
	//  copy �˰���� ���Թݺ��ڸ� ����ؼ� 
	// �����ð���

	ifstream in("�ҽ�.cpp");
	istream_iterator<char> p(in);

	char c;
	c = *p;

	//save("�ݺ��ڷ� cout �� �غ���.");

}