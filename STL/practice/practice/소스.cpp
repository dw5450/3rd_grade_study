/////////////////////////////////////////////////////////////////////////////////////////////
//2018.04.16		STL (월 23 , 화 56)					 7주 1
//
// 5장. 연관 컨테이너												정렬하는 이유, 빨리 찾기 위해서, 정렬의 기준이 되는 것이 키
//		정렬의 기준은 <(less 연산자)
//	set				- 키 값에 따라 정렬								기본 오름 차순을 한다/ 처음 값을 넣기는 힘들지만 찾기는 좋다. 겹치지 않아!
//	map				- 키와 밸류로 구성, 키가 정렬의 기준			가수 이름 : 노래 등
//	unordered_set	- 키값을 해싱하여 저장
//	unordered_map	- 키와 밸류로 구성 , 키값을 해싱하여 밸류를 저장할 곳을 지정
////내일 여기에서 시작합니다. Model 클레스를  mapㅇ에 넣어보자
///////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>					
#include <map>
#include <functional>
#include <algorithm>
#include <vector>
//다음 헤더는 실행시 지워야 할것입니다
#include "Model.h"							//모델을 사용할시 추가후 사용해 주세요
#include "save.h"
#include "funcSpeedCheck.h"
#include <fstream>
using namespace std;

//히어로와 전투력수치를 맵으로 만들어 보자

int main()
{
	string filename = "이상한 나라의 앨리스.txt";
	//이 파일은 UTF-8 형식의 파일로 BOM(Byte order makr)바이트가 기록되어 있다.
	// 3바이트를 무시해야 진짜 텍스트를 읽을 수 있다.
	ifstream in(filename);

	if (!in) {
		cout << filename << "을 열 수 없습니다." << endl;
		return 0;
	}

	char c;
	in >> c >> c >> c;		// BOM을 무시한다.

	map<string, int> simap;

	string s;
	while ( in  >> s){
		simap[s]++;
		//cimap.operater[](c)++;
	}

	// 가장 일이가 긴 단어는? (단어는 공백으로 분리됨)
	// STL에서 가능하면 for loop를 사용하지 않는다.(대신할 알고리즘이 있는 경우)
	auto p = max_element(simap.begin(), simap.end(), [](const auto & p1, const auto & p2) { return p1.first.length() < p2.first.length();});
	
	if (p != simap.end())
		cout << p->first << endl;
	
	//save("앨리스 파일에서 단어가 몇번 나오는지 찾아보자.txt");

}