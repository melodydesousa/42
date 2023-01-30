#ifndef HUMANA_H
# define HUMANA_H

# include <iostream>
# include <string>
# include <cctype>
# include "Weapon.hpp"

class	HumanA {

public:
	HumanA(std::string name, Weapon &weapon);
	~HumanA(void);

	void attack(void);

private:
	std::string _name;
	Weapon		&_weapon;
};

#endif