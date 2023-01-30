#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"


int main() {

	std::cout << "**********CLAPTRAP*********" << std::endl;
	
	ClapTrap toto("toto");

	toto.attack("Ennemy1");
	toto.takeDamage(8);
	toto.beRepaired(1);

	int i = 0;
	while (i < 10)
	{
		toto.attack("Ennemy1");
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

	std::cout << std::endl;
	std::cout << "**********FRAGTRAP*********" << std::endl;

	FragTrap tutu("tutu");

	tutu.takeDamage(10);
	tutu.highFiveGuys();
	tutu.attack("Ennemy2");
	tutu.takeDamage(90);
	tutu.highFiveGuys();

	std::cout << std::endl;
	std::cout << "**********DESTRUCTORS*********" << std::endl;

	
}