#ifndef FORM_H
# define FORM_H

# include <iostream>
# include <stdexcept>

class Bureaucrat;

class	Form {

public:
	Form(int gradeSign, int gradeExec, std::string name);
	Form(Form const &copy);
	~Form(void);
	Form& operator=(Form const &form);

	const std::string& getName(void) const;
	int getGradeExec(void) const;
	int getGradeSign(void) const;
	int getIfSigned(void) const;

	void beSigned(Bureaucrat& bureaucrat);
	void execute(Bureaucrat& bureaucrat);

	class GradeTooHighException : public std::exception
	{
		public:
			virtual const char* what() const throw()
			{
				return ("Grade is too high\n");
			}
	};

	class GradeTooLowException : public std::exception
	{
		public:
			virtual const char* what() const throw()
			{
				return ("Grade is too low\n");
			}
	};

private:
	const std::string _name;
	const int	_grade_exec;
	const int	_grade_sign;		
	bool _is_signed;
	
};

std::ostream& operator<<(std::ostream &out, Form const &form);


#endif
