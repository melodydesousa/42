#include "Zombie.hpp"

int main(){
	Zombie	*zombiehorde;
	int		N = 10;

	zombiehorde = zombieHorde(N, "zombie"); 	
	for (int i = 0; i < N; i++)
		zombiehorde->announce();
	delete[] zombiehorde;
	return 0;
}