#include "Zombie.hpp"

int main(){

	Zombie *newzombie = newZombie("newzombie");
	
	newzombie->announce();
	randomChump("ChumpZombie");
	randomChump("ChumpZombie2");

	delete newzombie;

	return 0;
}