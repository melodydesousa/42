#include "Bureaucrat.hpp"
#include "colors.h"

int main()
{
	std::cout << BOLD_YELLOW "grade = 0 -> TOO HIGH \n" RESET;
	try
	{
		Bureaucrat test("#1", 0);
		std::cout << test;
	}
	catch  (std::exception& e)
	{
		std::cout << e.what();
	}
	std::cout << BOLD_YELLOW "grade = 1 + increase -> TOO HIGH \n" RESET;
	try
	{
		Bureaucrat test("#2", 1);
		std::cout << test;
		test.increase_grade();
		std::cout << test;

	}
	catch  (std::exception& e)
	{
		std::cout << e.what();
	}
	std::cout << BOLD_YELLOW "grade = 21 + decrease -> NO EXCEPTION \n" RESET;
	try
	{
		Bureaucrat test("#3", 21);
		std::cout << test;
		test.decrease_grade();
		std::cout << test;

	}
	catch  (std::exception& e)
	{
		std::cout << e.what();
	}
	std::cout << BOLD_YELLOW "grade = 150 + set to 151 -> TOO LOW \n" RESET;
	try
	{
		Bureaucrat test("#4", 150);
		std::cout << test;
		test.setGrade(151);
		std::cout << test;

	}
	catch  (std::exception& e)
	{
		std::cout << e.what();
	}


	return 0;
}
