#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : Form(145, 137, "no name") {
	this->_target = target;
	std::cout << "Default ShrubberyCreationForm constructor called\n";
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &to_copy) : Form(145, 137, "no name") {
	std::cout << "Copy Form constructor called\n";
	*this = to_copy;
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(ShrubberyCreationForm const &cpy) {
	std::cout << "ShrubberyCreationForm operator = called\n";
	(void) cpy;
	return *this;
}

void ShrubberyCreationForm::action_form(Bureaucrat const & executor) {
	this->execute(executor);
	std::string	file = this->_target + "_shrubbery";
	std::ofstream file2(file.c_str());
	try {
		if (!file2.is_open())
			throw FileCantOPen();
	}
	catch (std::exception &e)
	{
		throw FileCantOPen();
	}
	file2 << "  //  \\   ";
	file2 << " //    \\  ";
	file2 << " |     | ";
	file2 << "  \\   //  ";
	file2 << "   | |   ";
	file2 << "   | |   ";
	file2 << "   //_\\   ";
	file2.close();
}


ShrubberyCreationForm::~ShrubberyCreationForm(void) {
	std::cout << "Destructor ShrubberyCreationForm called\n";
}