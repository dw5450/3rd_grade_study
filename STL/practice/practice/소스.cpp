/////////////////////////////////////////////////////////////////////////////////////////////
//2018.04.16		STL (월 23 , 화 56)					 7주 1
//
//
// 표준에 맞는 컨테이너와 반복자를 만들어보자

//9장 알고리즘
//	학과 자료실에서 "단어들.txt"를 다운받아 vector<string>에 읽어주세요.
//
///////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <map>
#include <list>

//다음 헤더는 실행시 지워야 할것입니다
//#include "Model.h"							//모델을 사용할시 추가후 사용해 주세요
#include "save.h"
using namespace std;

//원소를 수정하는 알고리즘

struct PS : pair<string, string>
{
	PS(string s) : pair<string, string>(s, s) {
		sort(first.begin(), first.end());

	}

	operator string() const { return second; };
};

int main()
{
	ifstream in("단어들.txt");

	vector<string> v{ istream_iterator<string>(in), istream_iterator<string>() };

	vector<PS> pv{ v.begin(), v.end() };

	string s;
	//first 기준으로 정렬한다.


	sort(pv.begin(), pv.end(), [](const PS & a, const  PS & b){
		return a.first < b.first;});

	map<string, std::list<string>> m;

	// 애너그램쌍을 찾아 적당한 컨테이너에 저장하라
	vector<PS>::const_iterator j, k, e;
	j = begin(pv);
	e = pv.end();

	int i = 1;

	while (true) {
		j = adjacent_find(j, e, [](const PS & a, const PS & b) {return a.first == b.first;});

		if (j == e)
			break;

		k = find_if_not(j, e, [&j](const PS& a) {
			return a.first == j->first;
		});
		//[j,k]는 애너그램이다.
		m.insert(make_pair(j->first, list<string>{ j,k }));

		j = k;
	}

	// 가장 갯수가 많은 애너그램은?

	auto result = max_element(begin(m), end(m), [](const pair < string, list<string>> & psl1, const pair < string, list<string>> & psl2)
	{return psl1.second.size() < psl2.second.size();});

	cout << result->first << endl;

	//사용자가 입력한 단어의anagram을 찾아줘

	while (true) {
		string s;
		cout << "단어를 입력하세요 : ";
		cin >> s;
		//여기를 코딩하세요
		
		string sort_s{ s };
		sort(begin(sort_s), end(sort_s));
		auto p = m.find(sort_s);

		if (p != m.end()) {
			cout << s << "의 애너그램입니다. -->";

			for (auto i = p->second.begin(); i != p->second.end(); ++i)
				cout << *i << "   ";
			cout << endl;
		}
		else {
			cout << "애너그램이 없는 단어입니다." << endl;
		}
		
	}
}