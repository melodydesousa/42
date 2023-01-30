#ifndef BUREAUCRAT_H
# define BUREAUCRAT_H

# include <iostream>
# include <stdexcept>

class Form;

class	Bureaucrat {

public:
	Bureaucrat(void);
	Bureaucrat(std::string name, int grade);
	Bureaucrat(Bureaucrat const &copy);
	~Bureaucrat(void);
	Bureaucrat& operator=(Bureaucrat const &bureaucrat);

	const std::string& getName(void) const;
	int getGrade(void) const;
	void setGrade(int grade);

	void increase_grade(void);
	void decrease_grade(void);

	void signForm(Form &form);
	void executeForm(Form const &form);

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
	int	_grade;

};

std::ostream& operator<<(std::ostream &out, Bureaucrat const &bureaucrat);


#endif
