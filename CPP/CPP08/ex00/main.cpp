#include "easyfind.hpp"
#include "colors.h"

int main() {
	std::cout << YELLOW "Vector test" RESET << std::endl;
	std::vector<int> vec(10, 0);
	vec.push_back(42);
	try 
	{
		int match = easyfind(vec, 42);
		std::cout << match << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
	}

	std::cout << YELLOW "List test" RESET << std::endl;
	std::list<int> list1(10, 4);
	list1.push_front(42);
	try 
	{
		int match = easyfind(list1, 4);
		std::cout << match << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
	}
	
	return 0;
}