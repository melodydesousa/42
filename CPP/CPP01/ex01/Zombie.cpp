#include "Zombie.hpp"

Zombie::Zombie(void) {
	std::cout << this->_name << "A zombie with no name has been created\n";
	return;
}

Zombie::~Zombie(void) {
	std::cout << this->_name << " destroyed\n";
	return;
}

void Zombie::announce(void) {
	std::cout << this->_name << ": BraiiiiiiinnnzzzZ...\n";
	return;
}

void Zombie::set_name(std::string name) {
	this->_name = name;
}