#include<iostream>

int main()
{
	std::cout << "Hello,world." << std::endl;

	std::cout << "输入两个数" << std::endl;
	int v1 = 0, v2 = 0;
	std::cin >> v1 >> v2;
	std::cout << v1 << "+" << v2 << "=" << v1 + v2 << std::endl;
			
	return 0;
}