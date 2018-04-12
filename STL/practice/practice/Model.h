#pragma once
#include <iostream>
using namespace std;
int gid = 0;

class Model {
private:
	static int gid;
	int id;
	char* data = nullptr;
	size_t size = 0;
public:
	Model() :id(++gid) { cout << id << " - 디폴트 생성자" << endl; }
	explicit Model(size_t s) :size(s), id(++gid) {
		data = new char[size];
		cout << id << " - 생성자	크기 : " << size << "	주소 : " << static_cast<void*>(data) << endl;
	}
	Model(const Model& m) :id(++gid) {
		size = m.size;
		data = new char[size];
		// 깊은 복사
		memcpy(data, m.data, size);

		cout << id << " - 복사 생성자	크기 : " << size << "		주소 : " << static_cast<void*>(data) << endl;
	}
	~Model() {
		cout << id << " - 소멸자	크기 : " << size << "		주소 : " << static_cast<void*>(data) << endl;
		if (data != nullptr)
			delete[] data;
	}
	Model& operator=(const Model& m) {	// 복사할당자
		if (this == &m)
			return *this;

		size = m.size;
		if (data != nullptr) {
			delete[] data;
		}
		data = new char[size];
		memcpy(data, m.data, size);

		cout << id << " - 복사할당자	크기 : " << size << "		주소 : " << static_cast<void*>(data) << endl;
		return *this;
	}
	// 이동 생성자, 이동 할당 연산자
	Model(Model&& other) :id(++gid) {
		size = other.size;
		data = other.data;
		// 원본은 well-known 상태로 만들어주자(defaul값)
		other.size = 0;
		other.data = 0;

		cout << id << " - 이동생성자	크기 : " << size << "		주소 : " << static_cast<void*>(data) << endl;
	}
	Model& operator=(Model&& other) {
		if (this == &other)
			return *this;

		size = other.size;
		if (data != nullptr) {
			delete[] data;
		}
		data = other.data;

		// 원본은 well-known 상태로 만들어주자(defaul값)
		other.size = 0;
		other.data = 0;

		cout << id << " - 이동할당 연산자		크기 : " << size << "		주소 : " << static_cast<void*>(data) << endl;
		return *this;
	}
	friend ostream& operator<<(ostream&, const Model&);

	int getSize()const { return size; }
};
int Model::gid = 0;
ostream& operator<<(ostream& os, const Model& m) {
	os << "아이디 : " << m.id << endl;
	os << "크기 : " << m.size << endl;
	os << "데이터 : " << static_cast<void*>(m.data) << endl;
	return os;
}