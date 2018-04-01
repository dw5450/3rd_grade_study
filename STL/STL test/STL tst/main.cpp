#include <iostream>
#include <memory>
#include <utility>
	
using namespace std;

int gid = 0;
class Model
{
	int id;
	char * data = nullptr;				//���� �Ҵ��� �޸��� ���۹���
	size_t size = 0;					//�޸��� ũ��



public:
	Model() : id(++gid) {
		cout << id << " - default ctor" << endl;		//������ ����
	}

	Model(int n) : size(n), id(++gid) {
		data = new char[n];
		cout << id << "������ - " << size << "����Ʈ, �ּ� : " << static_cast<void *>(data) << endl;		//������ ����
	}

	Model(const Model & other) : id(++gid) {
		size = other.size;

		data = new char[size];

		memcpy(data, other.data, size);	//deep copy
		cout << id << "���� ������, size_t : " << this->size << endl;		//������ ����
	}

	size_t getSize_t() const { return size; }
	char * getData() const { return data; }

	Model & operator=(const Model & other)
	{
		if (this == &other)
			return *this;

		size = other.size;
		if (data != nullptr)
			delete[] data;

		data = new char[size];

		memcpy(data, other.data, size);	//deep copy
		cout << "���� �Ҵ���, size_t : " << this->size << endl;		//������ ����

		return *this;
	}

	//�̵� ������ / �̵� �Ҵ� ������
	Model(Model && other) : id(++gid) {
		size = other.size;
		data = other.data;
		//������ well-known ���·� ��������� (default ��)
		other.size = 0;
		other.data = nullptr;
		cout << id << "�̵� ������, size_t : " << this->size << endl;		//������ ����


	}
	Model & operator=(Model && other) {
		if (this == &other)
			return *this;

		size = other.size;
		if (data != nullptr)
			delete[] data;

		this->size = other.size;
		this->data = other.data;
		other.size = 0;
		other.data = nullptr;
		cout << "�̵� �Ҵ���, size_t : " << this->size << endl;		//������ ����

		return *this;


	}


	~Model()
	{
		cout << id << "�Ҹ��� - " << size << "����Ʈ, �ּ� :" << static_cast<void *>(data) << endl;		//������ ����
		if (data != nullptr)
			delete[] data;
	}
};


int main()
{
	unique_ptr<Model> unique_ptr1{ new Model(100) };
	cout << unique_ptr1.get() << endl;

	unique_ptr<Model> unique_ptr2{ move (unique_ptr1) };
	cout << unique_ptr1.get() << endl;
	cout << unique_ptr2.get() << endl;
}
