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
			cout << "����� �Լ��� �̸� : " << name << endl;
		auto elapsedTime = chrono::high_resolution_clock::now() - begin;
		cout << "�Լ��� ���� �� �� ����� �ð�  = " << chrono::duration<double>(elapsedTime).count() << endl;
	}
};
#endif // !1


