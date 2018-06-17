/////////////////////////////////////////////////////////////////////////////////////////////
//2018.04.16		STL (�� 23 , ȭ 56)					 7�� 1
//
//
// ǥ�ؿ� �´� �����̳ʿ� �ݺ��ڸ� ������

//9�� �˰���
//	�а� �ڷ�ǿ��� "�ܾ��.txt"�� �ٿ�޾� vector<string>�� �о��ּ���.
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

//���� ����� ����� ������ �Ұ��Դϴ�
//#include "Model.h"							//���� ����ҽ� �߰��� ����� �ּ���
#include "save.h"
using namespace std;

//���Ҹ� �����ϴ� �˰���

struct PS : pair<string, string>
{
	PS(string s) : pair<string, string>(s, s) {
		sort(first.begin(), first.end());

	}

	operator string() const { return second; };
};

int main()
{
	ifstream in("�ܾ��.txt");

	vector<string> v{ istream_iterator<string>(in), istream_iterator<string>() };

	vector<PS> pv{ v.begin(), v.end() };

	string s;
	//first �������� �����Ѵ�.


	sort(pv.begin(), pv.end(), [](const PS & a, const  PS & b){
		return a.first < b.first;});

	map<string, std::list<string>> m;

	// �ֳʱ׷����� ã�� ������ �����̳ʿ� �����϶�
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
		//[j,k]�� �ֳʱ׷��̴�.
		m.insert(make_pair(j->first, list<string>{ j,k }));

		j = k;
	}

	// ���� ������ ���� �ֳʱ׷���?

	auto result = max_element(begin(m), end(m), [](const pair < string, list<string>> & psl1, const pair < string, list<string>> & psl2)
	{return psl1.second.size() < psl2.second.size();});

	cout << result->first << endl;

	//����ڰ� �Է��� �ܾ���anagram�� ã����

	while (true) {
		string s;
		cout << "�ܾ �Է��ϼ��� : ";
		cin >> s;
		//���⸦ �ڵ��ϼ���
		
		string sort_s{ s };
		sort(begin(sort_s), end(sort_s));
		auto p = m.find(sort_s);

		if (p != m.end()) {
			cout << s << "�� �ֳʱ׷��Դϴ�. -->";

			for (auto i = p->second.begin(); i != p->second.end(); ++i)
				cout << *i << "   ";
			cout << endl;
		}
		else {
			cout << "�ֳʱ׷��� ���� �ܾ��Դϴ�." << endl;
		}
		
	}
}