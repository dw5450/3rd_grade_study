#pragma once
#include <fstream> 
#include <chrono> 
#include <ctime> 
#include <string>

using namespace std;

//#define _CRT_SECURE_NO_WARNINGS

void save(string s) {
	// 강의가 저장된 시간을 기록하자 
	// main()이 있는 소스파일의 내용을 덧붙이기로 기록하자 

	ifstream in("소스.cpp");
	ofstream out(s, ios::app);

	auto tp = chrono::system_clock::now();
	auto t = chrono::system_clock::to_time_t(tp);

	//out << "-------------------------------------------------" << endl;
	//out << "강의시간: " << ctime(&t);
	//out << "-------------------------------------------------" << endl;

	char c;
	while (in.get(c)) {
		out.put(c);
	}
	out << endl;
}