#ifndef CLAPTRAP_H
# define CLAPTRAP_H

# include <iostream>
# include <string>
# include <cctype>
# include <stdlib.h>

class	ClapTrap {

public:

	ClapTrap(void);
	ClapTrap(std::string name);
	ClapTrap(ClapTrap const &copy);
	~ClapTrap(void);
	ClapTrap& operator=(ClapTrap const &claptrap);

	void attack(const std::string& target);
	void takeDamage(unsigned int amount);
	void beRepaired(unsigned int amount);

private:
	std::string _name;
	unsigned int	_hitpoints;
	unsigned int _energypoints;
	unsigned int _attackdamage;

};

#endif
