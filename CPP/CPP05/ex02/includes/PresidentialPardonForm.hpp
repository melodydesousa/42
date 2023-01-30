#ifndef PRESIDENTIALPARDONFORM_H
# define PRESIDENTIALPARDONFORM_H

# include <iostream>
# include <stdexcept>

class Bureaucrat;

class	PresidentialPardonForm : public Form
{

public:
	PresidentialPardonForm(int gradeSign, int gradeExec, std::string name);
	PresidentialPardonForm(PresidentialPardonForm const &copy);
	~PresidentialPardonForm(void);
	PresidentialPardonForm& operator=(PresidentialPardonForm const &cpy);

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

std::ostream& operator<<(std::ostream &out, PresidentialPardonForm const &p);


#endif
