#include <iostream>
#include <functional>
#include <string>

void invokeMe(const std::string& s) {
	std::cout << s << " : const " << std::endl;
}

template <class T>
void doubleMe(T t) {
	t *= 2;
}


int main() 
{
	std::string s("¹®ÀÚ¿­");

	invokeMe(std::ref(s));

	int i = 1;
	std::cout << i << std::endl;

	doubleMe(i);
	std::cout << i << std::endl;

	doubleMe(std::ref(i));
	std::cout << i << std::endl;


}