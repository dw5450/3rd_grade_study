#include <iostream>
#include <thread>

int main()
{
	// ���� �ð�
	auto beginTime = std::chrono::high_resolution_clock::now();

	std::cout << " ���ư��� �Լ� �Լ�" << std::endl;

	auto elapsedTime = std::chrono::high_resolution_clock::now() - beginTime;

	std::cout << "�Լ��� ���ư� �ð�: " << std::chrono::duration<double>(elapsedTime).count() << std::endl;


}