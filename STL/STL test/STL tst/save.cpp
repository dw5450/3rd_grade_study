
//번외편 세이브 파일 만들기 

#define _CRT_SECURE_NO_WARNINGS //위험 표시 에러 안뜨게 설정 
#include "save.h"
#include <fstream> 
#include <chrono> 
#include <ctime> 

using namespace std;

void save(void) {
	// 강의가 저장된 시간을 기록하자 
	// main()이 있는 소스파일의 내용을 덧붙이기로 기록하자 

	ifstream in("소스.cpp");
	ofstream out("2018 STL.txt", ios::app);

	auto tp = chrono::system_clock::now();
	auto t = chrono::system_clock::to_time_t(tp);

	out << "-------------------------------------------------" << endl;
	out << "강의시간: " << ctime(&t);
	out << "-------------------------------------------------" << endl;

	char c;
	while (in.get(c)) {
		out.put(c);
	}
	out << endl;
}

