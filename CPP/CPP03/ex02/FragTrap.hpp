#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

# include "ClapTrap.hpp"
# include <iostream>

class FragTrap : public ClapTrap
{
public :
	FragTrap(void);
	FragTrap(std::string name);
	FragTrap(FragTrap const &copy);
	FragTrap& operator=(FragTrap const &fragtrap);
	~FragTrap(void);

	void attack(const std::string& target);
	void highFiveGuys(void);

};

#endif