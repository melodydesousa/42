#include "RobotomyRequestForm.hpp"
// #include "Bureaucrat.hpp"

RobotomyRequestForm::RobotomyRequestForm(std::string target) : Form(72, 5, "no name") {
	this->_is_signed = false;
	std::cout << "Default RobotomyRequestForm constructor called\n";
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const &to_copy) : Form(72, 5, "no name") {
	std::cout << "Copy Form constructor called\n";
	*this = to_copy;
}

RobotomyRequestForm& RobotomyRequestForm::operator=(RobotomyRequestForm const &cpy) {
	std::cout << "RobotomyRequestForm operator = called\n";
	if (this != &cpy)
		this->_is_signed = cpy.getIfSigned();
	return *this;
}

int RobotomyRequestForm::getIfSigned(void) const {
	return (this->_is_signed);
}

RobotomyRequestForm::~RobotomyRequestForm(void) {
	std::cout << "Destructor RobotomyRequestForm called\n";
}

std::ostream& operator<<(std::ostream &out, RobotomyRequestForm const &p) {
	out << "\n";
	return out;
}