#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() {
	std::cout << "Default Bureaucrat constructor called\n";
}

Bureaucrat::Bureaucrat(const std::string name, int grade) : _name(name) {
	std::cout << "Constructor Bureaucrat with parameters called\n";
	if (grade < 1)
		throw GradeTooHighException();
	else if (grade > 150)
		throw GradeTooLowException();
	else
		this->_grade = grade;
}

Bureaucrat::Bureaucrat(Bureaucrat const &to_copy) : _name(to_copy.getName()) {
	std::cout << "Copy Bureaucrat constructor called\n";
	*this = to_copy;
}

Bureaucrat& Bureaucrat::operator=(Bureaucrat const &bureaucrat) {
	std::cout << "Bureaucrat operator = called\n";
	if (this != &bureaucrat)
		this->_grade = bureaucrat.getGrade();
	return *this;
}

const std::string& Bureaucrat::getName(void) const {
	return (this->_name);
}

int Bureaucrat::getGrade(void) const {
	return (this->_grade);
}

void Bureaucrat::increase_grade(void) {
	if (this->_grade == 1)
		throw GradeTooHighException();
	this->_grade--;
}

void Bureaucrat::setGrade(int grade) {
	if (grade < 1)
		throw GradeTooHighException();
	else if (grade > 150)
		throw GradeTooLowException();
	else
		this->_grade = grade;
}


void Bureaucrat::decrease_grade(void) {
	if (this->_grade == 150)
		throw GradeTooLowException();
	this->_grade++;
}

Bureaucrat::~Bureaucrat(void) {
	std::cout << "Destructor Bureaucrat called\n";
}

std::ostream& operator<<(std::ostream &out, Bureaucrat const &bureaucrat) {
	out << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << "\n";
	return out;
}
