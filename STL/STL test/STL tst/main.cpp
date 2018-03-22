#include <iostream>
#include <thread>

int main()
{
	// 시작 시간
	auto beginTime = std::chrono::high_resolution_clock::now();

	std::cout << " 돌아간다 함수 함수" << std::endl;

	auto elapsedTime = std::chrono::high_resolution_clock::now() - beginTime;

	std::cout << "함수가 돌아간 시간: " << std::chrono::duration<double>(elapsedTime).count() << std::endl;


}