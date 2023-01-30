#include "PresidentialPardonForm.hpp"
// #include "Bureaucrat.hpp"

PresidentialPardonForm::PresidentialPardonForm(std::string target) : Form(25, 5, "no name") {
	std::cout << "Default PresidentialPardonForm constructor called\n";
}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const &to_copy) : Form(25, 5, "no name") {
	std::cout << "Copy Form constructor called\n";
	*this = to_copy;
}

PresidentialPardonForm& PresidentialPardonForm::operator=(PresidentialPardonForm const &cpy) {
	std::cout << "PresidentialPardonForm operator = called\n";
	if (this != &cpy)
		this->_is_signed = cpy.getIfSigned();
	return *this;
}

int PresidentialPardonForm::getIfSigned(void) const {
	return (this->_is_signed);
}

PresidentialPardonForm::~PresidentialPardonForm(void) {
	std::cout << "Destructor PresidentialPardonForm called\n";
}


std::ostream& operator<<(std::ostream &out, PresidentialPardonForm const &p) {
	out << "\n";
	return out;
}