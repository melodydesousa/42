#include "HumanB.hpp"

HumanB::HumanB(std::string name) {
	this->_weapon = NULL;
	this->_name = name;
	return;
}

HumanB::~HumanB(void) {
	return;
}

void HumanB::attack(void) {
	std::cout << this->_name << " attacks with their " << this->_weapon->getType() << "\n";
}

void	HumanB::setWeapon(Weapon &weapon) {
	this->_weapon = &weapon;
	std::string type = weapon.getType();
	_weapon->setType(type);
	return;
}