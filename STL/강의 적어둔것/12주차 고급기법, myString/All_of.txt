/////////////////////////////////////////////////////////////////////////////////////////////
//2018.04.16		STL (월 23 , 화 56)					 7주 1
//
//
// 표준에 맞는 컨테이너와 반복자를 만들어보자
///////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>
#include <iterator>

//다음 헤더는 실행시 지워야 할것입니다
//#include "Model.h"							//모델을 사용할시 추가후 사용해 주세요
#include "save.h"
using namespace std;


template<class InIter, class Call>
bool my_all_of(InIter b, InIter e, Call f)
{
	if (b == e)
		return true;


	while ( b != e){
		if ( !f(*b) )
			return false;
		++b;
	}

	return true;
}

int main()
{
	int a[]{ 1, 4, 6, 8, 10 };
	//모두 짝수인지 검사하시오.

	bool result = my_all_of(begin(a), end(a), [](int n)
	{
		return !(n & 1);
	});

	if (result == true)
	{
		cout << " 모두 짝수입니다" << endl;
	}
	else {
		cout << "홀수가 존재합니다." << endl;
	}
}