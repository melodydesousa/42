#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void) : _hitpoints(10), _energypoints(10), _attackdamage(0)
{
	std::cout << "Default ClapTrap constructor called\n";
	return;
}

ClapTrap::ClapTrap(std::string name) : _name(name), _hitpoints(10), _energypoints(10), _attackdamage(0)
{
	std::cout << "Constructor ClapTrap with name called\n";
	return;
}

ClapTrap::ClapTrap(ClapTrap const &copy) {
	std::cout << "Copy ClapTrap constructor called\n";
	*this = copy;
	return;
}

ClapTrap& ClapTrap::operator=(ClapTrap const &claptrap) {
	if (this != &claptrap) {
		this->_attackdamage = claptrap._attackdamage;
		this->_energypoints = claptrap._energypoints;
		this->_hitpoints = claptrap._hitpoints;
	}
	return *this;
}

ClapTrap::~ClapTrap(void) {
	std::cout << "Destructor ClapTrap called\n";
	return;
}

void ClapTrap::attack(const std::string &target)
{
	if (this->_hitpoints == 0) {
		std::cout << "ClapTrap " << _name << " is dead\n";
		return ;
	}
	else if (this->_energypoints == 0) {
		std::cout << "ClapTrap " << _name << " has not enought energy points to do anything!\n";
		return ;
	}
	else
		this->_energypoints--;
	std::cout << "ClapTrap " << _name << " attacks " << target << ", causing "
		<< _attackdamage << " points of damage!" << " He has now " << this->_energypoints << " energy points left\n";
	return;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	if ((int)amount < 0)	{
		std::cout << "Amount is not valid\n";
		return ;
	}
	if ((int)(this->_hitpoints - amount) <= 0)
	{
		this->_hitpoints = 0;
		std::cout << "ClapTrap " << _name << " has lost too many hit points and died\n";
		return ;
	}
	else if (this->_hitpoints == 0)
	{
		std::cout << "ClapTrap " << _name << " is alredy dead\n";
		return ;
	}
	this->_hitpoints -= amount;
	std::cout << "ClapTrap " << _name << " took damage and lost " << amount << " hit points. He has now " << _hitpoints << " hit points left\n";
	return;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if ((int)amount < 0)	{
		std::cout << "Amount is not valid\n";
		return ;
	}
	if (this->_hitpoints == 0) {
		std::cout << "ClapTrap " << _name << " is dead\n";
		return ;
	}
	else if (this->_energypoints == 0) {
		std::cout << "ClapTrap " << _name << " has not enought energy points to do anything!\n";
		return ;
	}
	this->_energypoints--;
	this->_hitpoints += amount;
	std::cout << "ClapTrap " << _name << " is repaired, he gained " << amount << " hit points and has now " << _hitpoints << " hit points\n";
}
