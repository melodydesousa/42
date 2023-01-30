#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void) : ClapTrap()
{
	std::cout << "Default ScavTrap constructor called\n";
	this->_attackdamage = 20;
	this->_energypoints = 50;
	this->_hitpoints = 100;
	return;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	std::cout << "Constructor ScavTrap with name called\n";
	this->_name = name;
	this->_attackdamage = 20;
	this->_energypoints = 50;
	this->_hitpoints = 100;
	return;
}

ScavTrap::ScavTrap(ScavTrap const &copy) {
	std::cout << "Copy ScavTrap constructor called\n";
	*this = copy;
	return;
}

ScavTrap& ScavTrap::operator=(ScavTrap const &scavtrap) {
	if (this != &scavtrap) {
		this->_attackdamage = scavtrap._attackdamage;
		this->_energypoints = scavtrap._energypoints;
		this->_hitpoints = scavtrap._hitpoints;
	}
	return *this;
}

ScavTrap::~ScavTrap(void)
{
	std::cout << "Destructor ScavTrap called\n";
	return;
}

void ScavTrap::attack(const std::string &target)
{
	if (this->_hitpoints == 0) {
		std::cout << "ScavTrap " << _name << " is dead\n";
		return ;
	}
	else if (this->_energypoints == 0) {
		std::cout << "ScavTrap " << _name << " has not enought energy points to do anything!\n";
		return ;
	}
	else
		this->_energypoints--;
	std::cout << "ScavTrap " << _name << " attacks " << target << ", causing " 
		<< _attackdamage << " points of damage!" << " He has now " << this->_energypoints << " energy points left\n";;
	return;
}

void ScavTrap::guardGate(void) {
	if (this->_hitpoints > 0)
		std::cout << "ScavTrap " << _name << " has entered in Gate Keeper mode!\n";
}