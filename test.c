#include "file.h"
#include <iostream>

int main()
{
	writeToFile("example.txt", "Content");

	std::cout << readFromFile("example.txt") << std::endl;

	return 0;
}
