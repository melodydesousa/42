#ifndef SCAVTRAP_H
# define SCAVTRAP_H

# include <iostream>
# include <string>
# include <cctype>
# include "ClapTrap.hpp"

class	ScavTrap : public ClapTrap
{
	
public:
	ScavTrap(void);
	ScavTrap(std::string name);
	ScavTrap(ScavTrap const &copy);
	~ScavTrap(void);
	ScavTrap& operator=(ScavTrap const &claptrap);

	void attack(const std::string& target);
	void guardGate(void);

};


#endif