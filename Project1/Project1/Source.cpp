#include <iostream>
using namespace std;

int main()
{
	int* a = new int[5];
	for (unsigned i = 0; i < 5; ++i)
		a[i] = i + 10;

	std::cout << " a = ";
	for (unsigned i = 0; i < 5; ++i)
		std::cout << a[i] << " ";
	std::cout << "\n";
}