#ifndef ROBOTOMYREQUESTFORM_H
# define ROBOTOMYREQUESTFORM_H

# include <iostream>
# include <stdexcept>
# include "Form.hpp"
# include <stdlib.h>
# include <time.h> 

class Bureaucrat;

class	RobotomyRequestForm : public Form
{

public:
	RobotomyRequestForm(std::string target);
	RobotomyRequestForm(RobotomyRequestForm const &copy);
	~RobotomyRequestForm(void);
	RobotomyRequestForm& operator=(RobotomyRequestForm const &cpy);

	void action_form(Bureaucrat const & executor);

private:
	std::string _target;

};

#endif
