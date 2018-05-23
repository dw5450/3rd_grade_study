/////////////////////////////////////////////////////////////////////////////////////////////
//2018.04.16		STL (월 23 , 화 56)					 7주 1
//
// 7장. 반복자
//		반복자의 종류에 따라 다른 점
//		반복자의 종류를 판단하고 효율적인 알고리즘을 작성하는 법
///////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iterator>
#include <set>
#include <list>
#include <vector>
//다음 헤더는 실행시 지워야 할것입니다
#include "Model.h"							//모델을 사용할시 추가후 사용해 주세요
#include "save.h"
using namespace std;

template <class Iter>
int my_distance(Iter beg, Iter end)
{
	typename iterator_traits<Iter>::iterator_category c;
	if (strcmp(typeid(c).name(), "struct std::random_access_iterator_tag")) {
		cout << "연속적인 자료형" << endl;
		return end - beg;
	}
	else {
		int cnt{ 0 };
		while (beg != end) {
			cnt++;
			++beg;
		}

		return cnt;
	}

	return 0;
}

int main()
{
	list <int>list  {1, 2, 3, 4};

	cout << my_distance(list.begin(), list.end()) << endl;
	
	//f( vector<int>::iterator());		//이 함수는 반복자의 종류르를 화면에 출력한다.
//	save("반복자의 자료형의 이름을 적어보자.txt");

}