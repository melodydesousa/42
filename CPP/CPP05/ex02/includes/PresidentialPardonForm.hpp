#ifndef PRESIDENTIALPARDONFORM_H
# define PRESIDENTIALPARDONFORM_H

# include <iostream>
# include <stdexcept>
# include "Form.hpp"

class Bureaucrat;

class	PresidentialPardonForm : public Form
{

public:
	PresidentialPardonForm(std::string target);
	PresidentialPardonForm(PresidentialPardonForm const &copy);
	~PresidentialPardonForm(void);
	PresidentialPardonForm& operator=(PresidentialPardonForm const &cpy);
	
	void action_form(Bureaucrat const & executor);

private:
	std::string _target;
	
};

#endif
