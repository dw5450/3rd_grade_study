/////////////////////////////////////////////////////////////////////////////////////////////
//2018.04.16		STL (월 23 , 화 56)					 7주 1
//
// 5장. 연관 컨테이너												정렬하는 이유, 빨리 찾기 위해서, 정렬의 기준이 되는 것이 키
//		정렬의 기준은 <(less 연산자)
//	set				- 키 값에 따라 정렬								기본 오름 차순을 한다/ 처음 값을 넣기는 힘들지만 찾기는 좋다. 겹치지 않아!
//	map				- 키와 밸류로 구성, 키가 정렬의 기준			가수 이름 : 노래 등
//	unordered_set	- 키값을 해싱하여 저장
//	unordered_map	- 키와 밸류로 구성 , 키값을 해싱하여 밸류를 저장할 곳을 지정
///////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>					
#include <map>
#include <vector>
#include <random>
//다음 헤더는 실행시 지워야 할것입니다
#include "Model.h"							//모델을 사용할시 추가후 사용해 주세요
#include "save.h"
#include "funcSpeedCheck.h"
#include <fstream>
using namespace std;

//히어로와 전투력수치를 맵으로 만들어 보자

int main()
{
	ifstream alice_file("이상한 나라의 앨리스.txt");

	map<char, int> m1;

	char c;
	while (alice_file >> c) {
		m1[c]++;
	}

	for (const auto& data : m1) {
		cout << data.first << "\t" << data.second << endl;
	}


	alice_file.close();

	alice_file.open("이상한 나라의 앨리스.txt");

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


	//각 알파벳이 몇개씩 있는지 화면에 출력하라


	//save("map에 값을 찾아보자아.txt");

}