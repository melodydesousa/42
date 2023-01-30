#ifndef HUMANB_H
# define HUMANB_H

# include <iostream>
# include <string>
# include <cctype>
# include "Weapon.hpp"

class	HumanB {

public:
	HumanB(std::string name);
	~HumanB(void);

	void attack(void);
	void setWeapon(Weapon &weapon);

private:
	Weapon		*_weapon;
	std::string _name;
};

#endif