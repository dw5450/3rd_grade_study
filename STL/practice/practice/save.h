#pragma once
#include <fstream> 
#include <chrono> 
#include <ctime> 
#include <string>

using namespace std;

//#define _CRT_SECURE_NO_WARNINGS

void save(string s) {
	// ���ǰ� ����� �ð��� ������� 
	// main()�� �ִ� �ҽ������� ������ �����̱�� ������� 

	ifstream in("�ҽ�.cpp");
	ofstream out(s, ios::app);

	auto tp = chrono::system_clock::now();
	auto t = chrono::system_clock::to_time_t(tp);

	//out << "-------------------------------------------------" << endl;
	//out << "���ǽð�: " << ctime(&t);
	//out << "-------------------------------------------------" << endl;

	char c;
	while (in.get(c)) {
		out.put(c);
	}
	out << endl;
}