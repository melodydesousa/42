#include "Zombie.hpp"

Zombie::Zombie(std::string name) {
	this->_name = name;
	std::cout << this->_name << " has been created\n";
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
