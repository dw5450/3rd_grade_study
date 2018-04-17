/////////////////////////////////////////////////////////////////////////////////////////////
//2018.04.16		STL (월 23 , 화 56)					 7주 1
//
//4장 순차컨테이너(sequence container)
//
//중각 시험. 4. 24(화 :  8주 2)
//array, vector, deque, list, forward_list
//
//알고리즘 함수 find와 find_if를 이해하고 만들업자
//알고리즘 함수는 접미사가 붙는 버전이 따로 있다.
//if 접미사 - 조건에 따라 다르게 동작하는 버전
//		조건을 결정하는 호출가능탑입을 predicate이라고 부른다.
//		(bool 값을 리턴하는 함수를 말한다.)
///////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <list>
#include <algorithm>
//다음 헤더는 실행시 지워야 할것입니다
#include "Model.h"							//모델을 사용할시 추가후 사용해 주세요
#include "save.h"
#include "funcSpeedCheck.h"
using namespace std;


//find		: 찾고자 하는 값과 같은 값을 갖는 원소의 위치를 반환
//		-값이 같다는 것을 어떻게 만족하지?
//find_if	: 찾고자 하는 조건을 만족하는 원소의 위치를 반환한다. 
//무엇이 나와 똑같다고 할 수 있나...?
//똑같다는 연산자를 만족하면 -> 프로그래머 마음대로

template<class Iter, class Val>
Iter myFind(Iter b, Iter e, Val val)
{
	while (b != e) {
		if (*b == val)
			return b;
		++b;
	}
	return e;
}

int main()
{
	int a[]{ 1,2,3,4,5,6,7 };
	list<Model> v{ Model(1), Model(22), Model(333), Model(4444), Model(55555) };

	//v에서 첫 홀수의 위치를 찾아라

	auto p = myFind(v.begin(), v.end(), Model(333));


	if (p != v.end())
		cout << " 찾음" << endl;
	else
		cout << "원하는 값이 없다." << endl;

	
	//다음 명령어는 실행시 지워야 할 것 입니다.
	save("0417 모델을 find로 찾아보자.txt");					//저장할 파일명을 입력 해 주세요


}