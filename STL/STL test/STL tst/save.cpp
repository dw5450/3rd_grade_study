
//������ ���̺� ���� ����� 

#define _CRT_SECURE_NO_WARNINGS //���� ǥ�� ���� �ȶ߰� ���� 
#include "save.h"
#include <fstream> 
#include <chrono> 
#include <ctime> 

using namespace std;

void save(void) {
	// ���ǰ� ����� �ð��� ������� 
	// main()�� �ִ� �ҽ������� ������ �����̱�� ������� 

	ifstream in("�ҽ�.cpp");
	ofstream out("2018 STL.txt", ios::app);

	auto tp = chrono::system_clock::now();
	auto t = chrono::system_clock::to_time_t(tp);

	out << "-------------------------------------------------" << endl;
	out << "���ǽð�: " << ctime(&t);
	out << "-------------------------------------------------" << endl;

	char c;
	while (in.get(c)) {
		out.put(c);
	}
	out << endl;
}

