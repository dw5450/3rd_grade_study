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
	Model() :id(++gid) { cout << id << " - ����Ʈ ������" << endl; }
	explicit Model(size_t s) :size(s), id(++gid) {
		data = new char[size];
		cout << id << " - ������	ũ�� : " << size << "	�ּ� : " << static_cast<void*>(data) << endl;
	}
	Model(const Model& m) :id(++gid) {
		size = m.size;
		data = new char[size];
		// ���� ����
		memcpy(data, m.data, size);

		cout << id << " - ���� ������	ũ�� : " << size << "		�ּ� : " << static_cast<void*>(data) << endl;
	}
	~Model() {
		cout << id << " - �Ҹ���	ũ�� : " << size << "		�ּ� : " << static_cast<void*>(data) << endl;
		if (data != nullptr)
			delete[] data;
	}
	Model& operator=(const Model& m) {	// �����Ҵ���
		if (this == &m)
			return *this;

		size = m.size;
		if (data != nullptr) {
			delete[] data;
		}
		data = new char[size];
		memcpy(data, m.data, size);

		cout << id << " - �����Ҵ���	ũ�� : " << size << "		�ּ� : " << static_cast<void*>(data) << endl;
		return *this;
	}
	// �̵� ������, �̵� �Ҵ� ������
	Model(Model&& other) :id(++gid) {
		size = other.size;
		data = other.data;
		// ������ well-known ���·� ���������(defaul��)
		other.size = 0;
		other.data = 0;

		cout << id << " - �̵�������	ũ�� : " << size << "		�ּ� : " << static_cast<void*>(data) << endl;
	}
	Model& operator=(Model&& other) {
		if (this == &other)
			return *this;

		size = other.size;
		if (data != nullptr) {
			delete[] data;
		}
		data = other.data;

		// ������ well-known ���·� ���������(defaul��)
		other.size = 0;
		other.data = 0;

		cout << id << " - �̵��Ҵ� ������		ũ�� : " << size << "		�ּ� : " << static_cast<void*>(data) << endl;
		return *this;
	}
	friend ostream& operator<<(ostream&, const Model&);

	int getSize()const { return size; }
};
int Model::gid = 0;
ostream& operator<<(ostream& os, const Model& m) {
	os << "���̵� : " << m.id << endl;
	os << "ũ�� : " << m.size << endl;
	os << "������ : " << static_cast<void*>(m.data) << endl;
	return os;
}