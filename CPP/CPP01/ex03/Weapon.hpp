#ifndef WEAPON_H
# define WEAPON_H

# include <iostream>
# include <string>
# include <cctype>

class	Weapon {

public:
	Weapon(std::string type);
	Weapon(void);
	~Weapon(void);

	std::string const &getType(void);
	void setType(std::string new_type);

private:
	std::string _type;
};

#endif