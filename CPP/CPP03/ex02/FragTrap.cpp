#include "FragTrap.hpp"

FragTrap::FragTrap(void) : ClapTrap()
{
	std::cout << "Default FragTrap constructor called\n";
	this->_attackdamage = 30;
	this->_energypoints = 100;
	this->_hitpoints = 100;
	return;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	std::cout << "Constructor FragTrap with name called\n";
	this->_name = name;
	this->_attackdamage = 30;
	this->_energypoints = 100;
	this->_hitpoints = 100;
	return;
}

FragTrap::FragTrap(FragTrap const &copy) {
	std::cout << "Copy FragTrap constructor called\n";
	*this = copy;
	return;
}

FragTrap& FragTrap::operator=(FragTrap const &fragtrap) {
	if (this != &fragtrap) {
		this->_attackdamage = fragtrap._attackdamage;
		this->_energypoints = fragtrap._energypoints;
		this->_hitpoints = fragtrap._hitpoints;
	}
	return *this;
}

void FragTrap::attack(const std::string &target)
{
	if (this->_hitpoints == 0) {
		std::cout << "FragTrap " << _name << " is dead\n";
		return ;
	}
	else if (this->_energypoints == 0) {
		std::cout << "FragTrap " << _name << " has not enought energy points to do anything!\n";
		return ;
	}
	else
		this->_energypoints--;
	std::cout << "FragTrap " << _name << " attacks " << target << ", causing " 
		<< _attackdamage << " points of damage!" << " He has now " << this->_energypoints << " energy points left\n";;
	return;
}

void FragTrap::highFiveGuys(void){
	if (this->_hitpoints > 0)
		std::cout << "FragTrap " << _name << " would like to high five!\n";
}

FragTrap::~FragTrap(void)
{
	std::cout << "Destructor FragTrap called\n";
	return;
}
