/////////////////////////////////////////////////////////////////////////////////////////////
//2018.04.16		STL (�� 23 , ȭ 56)					 7�� 1
//
// 7��. �ݺ���
//		�ݺ����� ������ ���� �ٸ� ��
//		�ݺ����� ������ �Ǵ��ϰ� ȿ������ �˰����� �ۼ��ϴ� ��
///////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iterator>
#include <set>
#include <list>
#include <vector>
//���� ����� ����� ������ �Ұ��Դϴ�
#include "Model.h"							//���� ����ҽ� �߰��� ����� �ּ���
#include "save.h"
using namespace std;

template <class Iter>
int my_distance(Iter beg, Iter end)
{
	typename iterator_traits<Iter>::iterator_category c;
	if (strcmp(typeid(c).name(), "struct std::random_access_iterator_tag")) {
		cout << "�������� �ڷ���" << endl;
		return end - beg;
	}
	else {
		int cnt{ 0 };
		while (beg != end) {
			cnt++;
			++beg;
		}

		return cnt;
	}

	return 0;
}

int main()
{
	list <int>list  {1, 2, 3, 4};

	cout << my_distance(list.begin(), list.end()) << endl;
	
	//f( vector<int>::iterator());		//�� �Լ��� �ݺ����� �������� ȭ�鿡 ����Ѵ�.
//	save("�ݺ����� �ڷ����� �̸��� �����.txt");

}