#ifndef ROBOTOMYREQUESTFORM_H
# define ROBOTOMYREQUESTFORM_H

# include <iostream>
# include <stdexcept>

class Bureaucrat;

class	RobotomyRequestForm : public Form
{

public:
	RobotomyRequestForm(int gradeSign, int gradeExec, std::string name);
	RobotomyRequestForm(RobotomyRequestForm const &copy);
	~RobotomyRequestForm(void);
	RobotomyRequestForm& operator=(RobotomyRequestForm const &cpy);

	int getIfSigned(void) const;

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

};

std::ostream& operator<<(std::ostream &out, RobotomyRequestForm const &p);


#endif
