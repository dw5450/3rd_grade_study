/////////////////////////////////////////////////////////////////////////////////////////////
//2018.04.16		STL (월 23 , 화 56)					 7주 1
//
//4장 순차컨테이너(sequence container)
//
//중각 시험. 4. 24(화 :  8주 2)
//array, vector, deque, list, forward_list
//
//list의 멤버 함수 remove
//---> 컨테이너의 원소를 삭제하는 방식
///////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <list>
#include <algorithm>
//다음 헤더는 실행시 지워야 할것입니다
#include "Model.h"							//모델을 사용할시 추가후 사용해 주세요
#include "save.h"
#include "funcSpeedCheck.h"
using namespace std;

// 두 리스트를 하나로 합친다.


int main()
{
	list<int> a{ 1, 1, 1, 3, 3, 3, 5, 4, 7, 5, 7, 9 };
	a.unique();								//정렬한걸 날릴때만
	
	save("0417 리스트의 unique를 사용해보자.txt");					//저장할 파일명을 입력 해 주세요


}
