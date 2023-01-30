#include "ShrubberyCreationForm.hpp"
// #include "Bureaucrat.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : Form(145, 137, "no name") {
	std::cout << "Default ShrubberyCreationForm constructor called\n";
	this->_is_signed = false;
	std::string	file = target + "_shrubbery";
	std::ofstream file2(file.c_str());
	if (!file2.is_open())
		return (std::cout << "Error opening file\n", 1);
	file2 << "    -\n\";
	file2 << " 	/   \\n\";
	file2 << " /     \\n\";
	file2 << " {      }\n\";
	file2 << " \ - - /\n\";
	file2 << " ~ \ //  ~\n\";
	file2 << " - || - \n\";
	file2 << " - || -_\n\";
	file2 << " 	//\\\n";
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &to_copy) : Form(145, 137, "no name") {
	std::cout << "Copy Form constructor called\n";
	*this = to_copy;
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(ShrubberyCreationForm const &cpy) {
	std::cout << "ShrubberyCreationForm operator = called\n";
	if (this != &cpy)
		this->_is_signed = cpy.getIfSigned();
	return *this;
}

int ShrubberyCreationForm::getIfSigned(void) const {
	return (this->_is_signed);
}

ShrubberyCreationForm::~ShrubberyCreationForm(void) {
	std::cout << "Destructor ShrubberyCreationForm called\n";
}


std::ostream& operator<<(std::ostream &out, ShrubberyCreationForm const &p) {
	out << "\n";
	return out;
}