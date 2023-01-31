#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(std::string target) : Form(72, 5, "no name") {
	this->_target = target;
	std::cout << "Default RobotomyRequestForm constructor called\n";
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const &to_copy) : Form(72, 5, "no name") {
	std::cout << "Copy Form constructor called\n";
	*this = to_copy;
}

RobotomyRequestForm& RobotomyRequestForm::operator=(RobotomyRequestForm const &cpy) {
	std::cout << "RobotomyRequestForm operator = called\n";
	(void) cpy;
	return *this;
}

void RobotomyRequestForm::action_form(Bureaucrat const & executor) {
	this->execute(executor);
	std::cout << "* Drill sounds *\n";
	std::srand(std::time(0));
	for (int i = 0; i < 100; i++) {
		if (std::rand() % 2 == 0)
			std::cout << this->_target << " has been Robotimized!/n";
		else
			std::cout << this->_target << "'s robotimization failed!/n";
	}
}

RobotomyRequestForm::~RobotomyRequestForm(void) {
	std::cout << "Destructor RobotomyRequestForm called\n";
}
