/////////////////////////////////////////////////////////////////////////////////////////////
//2018.04.16		STL (월 23 , 화 56)					 7주 1
//
// 7장 반복자

//
///////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iterator>
#include <stack>
#include <fstream>
//다음 헤더는 실행시 지워야 할것입니다
#include "Model.h"							//모델을 사용할시 추가후 사용해 주세요
#include "save.h"
#include "funcSpeedCheck.h"
using namespace std;

//반복자(모든 종류의 반복자가 지원)라면 지원해야 하는 연산
// *	: 역참조(dereferencing)
//==	: 비교 (comaprision)
//=		: 할당 (assignment)

//반복자의 종류 (Catergory)
//입출력반복자
//전진반복자++;
//전후진반복자(양방향 반복자) ++, --;
//랜덤반복자 +=, -=;
class MyHash {
	public:
		size_t operator()(const Model & a) const {
			hash<int> hashVal;
			
			return hashVal(a.getSize());

		}

};
int main()
{
	//	소스.cpp를 읽고 출력
	//	입출력자 반복자를 사용해서 작성해 봅니다.
	//  copy 알고리즘과 삽입반복자를 사용해서 
	// 다음시간에

	ifstream in("소스.cpp");
	istream_iterator<char> p(in);

	char c;
	c = *p;

	//save("반복자로 cout 을 해보자.");

}