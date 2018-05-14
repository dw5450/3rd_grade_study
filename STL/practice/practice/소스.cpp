/////////////////////////////////////////////////////////////////////////////////////////////
//2018.04.16		STL (�� 23 , ȭ 56)					 7�� 1
//
// 5��. ���� �����̳�												�����ϴ� ����, ���� ã�� ���ؼ�, ������ ������ �Ǵ� ���� Ű
//		������ ������ <(less ������)
//	set				- Ű ���� ���� ����								�⺻ ���� ������ �Ѵ�/ ó�� ���� �ֱ�� �������� ã��� ����. ��ġ�� �ʾ�!
//	map				- Ű�� ����� ����, Ű�� ������ ����			���� �̸� : �뷡 ��
//	unordered_set	- Ű���� �ؽ��Ͽ� ����
//	unordered_map	- Ű�� ����� ���� , Ű���� �ؽ��Ͽ� ����� ������ ���� ����
///////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>					
#include <map>
#include <vector>
#include <random>
//���� ����� ����� ������ �Ұ��Դϴ�
#include "Model.h"							//���� ����ҽ� �߰��� ����� �ּ���
#include "save.h"
#include "funcSpeedCheck.h"
#include <fstream>
using namespace std;

//����ο� �����¼�ġ�� ������ ����� ����

int main()
{
	ifstream alice_file("�̻��� ������ �ٸ���.txt");

	map<char, int> m1;

	char c;
	while (alice_file >> c) {
		m1[c]++;
	}

	for (const auto& data : m1) {
		cout << data.first << "\t" << data.second << endl;
	}


	alice_file.close();

	alice_file.open("�̻��� ������ �ٸ���.txt");

	map<string, int>m2;
	string s;
	while (alice_file >> s)
	{
		m2[s]++;
	}
	alice_file.close();

	multimap<int, string > m3;
	
	for (auto& data : m2) {
		m3.emplace(data.second, data.first);
		//m3[data.second] = data.first;
	}

	for (const auto& data : m3) {
		cout << data.first << "\t" << data.second << endl;
	}

	multimap<int, string > m4;
	for (const auto& data : m2) {
		m4.emplace(data.first.length(), data.first);
	}

	for (const auto& data : m4) {
		cout << data.first << "\t" << data.second << endl;
	}


	//�� ���ĺ��� ��� �ִ��� ȭ�鿡 ����϶�


	//save("map�� ���� ã�ƺ��ھ�.txt");

}