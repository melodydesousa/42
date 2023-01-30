#include "ClapTrap.hpp"

int main() {

	std::cout << "**********TOTO*********" << std::endl;
	ClapTrap toto("Toto");
	toto.takeDamage(-5);
	toto.attack("Ennemy1");
	toto.beRepaired(1);
	
	std::cout << std::endl;
	
	std::cout << "**********TITI*********" << std::endl;
	ClapTrap titi("Titi");
	titi.takeDamage(9);
	titi.attack("Ennemy2");
	
	std::cout << std::endl;

	return 0;
}
