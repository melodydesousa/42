#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(std::string target) : Form(25, 5, "no name") {
	this->_target = target;
	std::cout << "Default PresidentialPardonForm constructor called\n";
}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const &to_copy) : Form(25, 5, "no name") {
	std::cout << "Copy Form constructor called\n";
	*this = to_copy;
}

PresidentialPardonForm& PresidentialPardonForm::operator=(PresidentialPardonForm const &cpy) {
	std::cout << "PresidentialPardonForm operator = called\n";
	(void) cpy;
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm(void) {
	std::cout << "Destructor PresidentialPardonForm called\n";
}

void PresidentialPardonForm::action_form(Bureaucrat const & executor) {
	this->execute(executor);
	std::cout << this->_target << " has been forgiven by Zaphod Beeblebrox\n";
}