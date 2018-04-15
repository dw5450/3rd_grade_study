#pragma once
#ifndef __FUNC_SPPED_CHECK__
#define __FUNC_SPPED_CHECK__

#include<iostream>
#include<string>
#include<chrono>
using namespace std;
class funcSpeedCheck
{
	string name = "";
	chrono::time_point<chrono::steady_clock> begin = chrono::high_resolution_clock::now();
public:
	funcSpeedCheck() {};

	funcSpeedCheck(string s) {
		name = s;
	};


	~funcSpeedCheck()
	{
		if (name != "")
			cout << "실행된 함수의 이름 : " << name << endl;
		auto elapsedTime = chrono::high_resolution_clock::now() - begin;
		cout << "함수가 실행 할 때 경과된 시간  = " << chrono::duration<double>(elapsedTime).count() << endl;
	}
};
#endif // !1


