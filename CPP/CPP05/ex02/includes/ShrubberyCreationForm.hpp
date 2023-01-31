#ifndef SHRUBBERYCREATIONFORM_H
# define SHRUBBERYCREATIONFORM_H

# include <iostream>
# include <stdexcept>
# include <fstream>
# include "Form.hpp"

class Bureaucrat;

class	ShrubberyCreationForm : public Form
{

public:
	ShrubberyCreationForm(std::string target);
	ShrubberyCreationForm(ShrubberyCreationForm const &copy);
	~ShrubberyCreationForm(void);
	ShrubberyCreationForm& operator=(ShrubberyCreationForm const &cpy);

	void action_form(Bureaucrat const & executor);

private:
	std::string _target;

};

#endif
