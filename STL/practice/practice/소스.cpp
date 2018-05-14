/////////////////////////////////////////////////////////////////////////////////////////////
//2018.04.16		STL (�� 23 , ȭ 56)					 7�� 1
//
// 5��. ���� �����̳�												�����ϴ� ����, ���� ã�� ���ؼ�, ������ ������ �Ǵ� ���� Ű
//		������ ������ <(less ������)
//	set				- Ű ���� ���� ����								�⺻ ���� ������ �Ѵ�/ ó�� ���� �ֱ�� �������� ã��� ����. ��ġ�� �ʾ�!
//	map				- Ű�� ����� ����, Ű�� ������ ����			���� �̸� : �뷡 ��
//	unordered_set	- Ű���� �ؽ��Ͽ� ����
//	unordered_map	- Ű�� ����� ���� , Ű���� �ؽ��Ͽ� ����� ������ ���� ����
////���� ���⿡�� �����մϴ�. Model Ŭ������  map���� �־��
///////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>					
#include <map>
#include <functional>
#include <algorithm>
#include <vector>
//���� ����� ����� ������ �Ұ��Դϴ�
#include "Model.h"							//���� ����ҽ� �߰��� ����� �ּ���
#include "save.h"
#include "funcSpeedCheck.h"
#include <fstream>
using namespace std;

//����ο� �����¼�ġ�� ������ ����� ����

int main()
{
	string filename = "�̻��� ������ �ٸ���.txt";
	//�� ������ UTF-8 ������ ���Ϸ� BOM(Byte order makr)����Ʈ�� ��ϵǾ� �ִ�.
	// 3����Ʈ�� �����ؾ� ��¥ �ؽ�Ʈ�� ���� �� �ִ�.
	ifstream in(filename);

	if (!in) {
		cout << filename << "�� �� �� �����ϴ�." << endl;
		return 0;
	}

	char c;
	in >> c >> c >> c;		// BOM�� �����Ѵ�.

	map<string, int> simap;

	string s;
	while ( in  >> s){
		simap[s]++;
		//cimap.operater[](c)++;
	}

	// ���� ���̰� �� �ܾ��? (�ܾ�� �������� �и���)
	// STL���� �����ϸ� for loop�� ������� �ʴ´�.(����� �˰����� �ִ� ���)
	auto p = max_element(simap.begin(), simap.end(), [](const auto & p1, const auto & p2) { return p1.first.length() < p2.first.length();});
	
	if (p != simap.end())
		cout << p->first << endl;
	
	//save("�ٸ��� ���Ͽ��� �ܾ ��� �������� ã�ƺ���.txt");

}