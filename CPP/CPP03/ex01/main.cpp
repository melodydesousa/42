#include "ClapTrap.hpp"
#include "ScavTrap.hpp"


int main() {

	std::cout << "**********CLAPTRAP*********" << std::endl;
	
	ClapTrap toto("toto");

	toto.attack("Ennemy1");
	toto.takeDamage(8);

	int i = 0;
	while (i < 8)
	{
		toto.beRepaired(1);
		i++;
	}
	
	std::cout << std::endl;
	std::cout << "**********SCAVTRAP*********" << std::endl;

	ScavTrap titi("titi");

	titi.guardGate();
	titi.takeDamage(1);
	titi.attack("Ennemy2");
	titi.takeDamage(99);
	titi.guardGate();
	
}