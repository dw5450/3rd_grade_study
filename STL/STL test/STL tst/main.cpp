#include <iostream>
#include <memory>
#include <utility>
	
using namespace std;

int gid = 0;
class Model
{
	int id;
	char * data = nullptr;				//동적 할당한 메모리의 시작번지
	size_t size = 0;					//메모리의 크기



public:
	Model() : id(++gid) {
		cout << id << " - default ctor" << endl;		//생성자 관찰
	}

	Model(int n) : size(n), id(++gid) {
		data = new char[n];
		cout << id << "생성자 - " << size << "바이트, 주소 : " << static_cast<void *>(data) << endl;		//생성자 관찰
	}

	Model(const Model & other) : id(++gid) {
		size = other.size;

		data = new char[size];

		memcpy(data, other.data, size);	//deep copy
		cout << id << "복사 생성자, size_t : " << this->size << endl;		//생성자 관찰
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
		cout << "복사 할당자, size_t : " << this->size << endl;		//생성자 관찰

		return *this;
	}

	//이동 생성자 / 이동 할당 연산자
	Model(Model && other) : id(++gid) {
		size = other.size;
		data = other.data;
		//원본은 well-known 상태로 만들어주자 (default 값)
		other.size = 0;
		other.data = nullptr;
		cout << id << "이동 생성자, size_t : " << this->size << endl;		//생성자 관찰


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
		cout << "이동 할당자, size_t : " << this->size << endl;		//생성자 관찰

		return *this;


	}


	~Model()
	{
		cout << id << "소멸자 - " << size << "바이트, 주소 :" << static_cast<void *>(data) << endl;		//생성자 관찰
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
