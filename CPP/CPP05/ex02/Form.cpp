#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form(int gradeSign, int gradeExec, std::string name) : _name(name), _grade_exec(gradeExec), _grade_sign(gradeSign)  {
	std::cout << "Default Form constructor called\n";
	this->_is_signed = 0;
	if (gradeExec < 1 || gradeSign < 1)
		throw GradeTooHighException();
	else if (gradeExec > 150 || gradeSign > 150)
		throw GradeTooLowException();
}

Form::Form(Form const &to_copy) : _grade_exec(to_copy.getGradeExec()), _grade_sign(to_copy.getGradeSign()) {
	std::cout << "Copy Form constructor called\n";
	*this = to_copy;
}

Form& Form::operator=(Form const &form) {
	std::cout << "Form operator = called\n";
	if (this != &form)
		this->_is_signed = form.getIfSigned();
	return *this;
}

Form::~Form(void) {
	std::cout << "Destructor Form called\n";
}

const std::string& Form::getName(void) const {
	return (this->_name);
}

int Form::getGradeExec(void) const {
	return (this->_grade_exec);
}

int Form::getIfSigned(void) const {
	return (this->_is_signed);
}

int Form::getGradeSign(void) const {
	return (this->_grade_sign);
}

void Form::beSigned(Bureaucrat& bureaucrat) {
	if (bureaucrat.getGrade() <= this->_grade_sign)
		this->_is_signed = true;
	else
		throw GradeTooLowException();
}

void Form::execute(Bureaucrat const & bureaucrat) {
	return;
}


std::ostream& operator<<(std::ostream &out, Form const &form) {
	out << form.getName() << " requires a grade of <= " << form.getGradeSign() << " to be signed and a grade of <= " << form.getGradeExec() << " to be executed\n";
	return out;
}