#ifndef SHRUBBERYCREATIONFORM_H
# define SHRUBBERYCREATIONFORM_H

# include <iostream>
# include <stdexcept>

class Bureaucrat;

class	ShrubberyCreationForm : public Form
{

public:
	ShrubberyCreationForm(int gradeSign, int gradeExec, std::string name);
	ShrubberyCreationForm(ShrubberyCreationForm const &copy);
	~ShrubberyCreationForm(void);
	ShrubberyCreationForm& operator=(ShrubberyCreationForm const &cpy);

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

std::ostream& operator<<(std::ostream &out, ShrubberyCreationForm const &p);


#endif
