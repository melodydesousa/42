#include "Span.hpp"
#include "colors.h"

int main()
{
	std::cout << YELLOW "Subject test" RESET << std::endl;
	Span sp = Span(10);
	try 
	{
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);

		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
	}

	std::cout << YELLOW "Test with 100.000 numbers" RESET << std::endl;
	try 
	{
		Span big_sp = Span(100000);
		for (int i = 0; i < 100000; i++)
		{
			big_sp.addNumber(i);
		}

		std::cout << big_sp.shortestSpan() << std::endl;
		std::cout << big_sp.longestSpan() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
	}

	std::cout << YELLOW "Add range of iterators" RESET << std::endl;

	try 
	{
		std::vector<int> vec;
		vec.push_back(2);
		vec.push_back(4);
		vec.push_back(6);
		vec.push_back(8);
		vec.push_back(10);

		sp.addRange(vec.begin() + 2, vec.end());
		//print
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
	}

	std::cout << YELLOW "Add range of iterators already too many numbers" RESET << std::endl;

	try 
	{
		std::vector<int> vec;
		vec.push_back(2);
		vec.push_back(4);
		vec.push_back(4);
		vec.push_back(4);

		sp.addRange(vec.begin(), vec.end());
		//print
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
	}

	std::cout << YELLOW "No numbers" RESET << std::endl;
	try 
	{
		Span s = Span(0);
		std::cout << s.shortestSpan() << std::endl;
		std::cout << s.longestSpan() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
	}

	std::cout << YELLOW "Only 1 number" RESET << std::endl;
	try 
	{
		Span ss = Span(10);
		ss.addNumber(2);
		std::cout << ss.shortestSpan() << std::endl;
		std::cout << ss.longestSpan() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
	}
	return 0;
}
