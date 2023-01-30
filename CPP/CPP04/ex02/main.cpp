#include "Animal.hpp"
#include "WrongAnimal.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"
#include "Dog.hpp"
#include "Brain.hpp"
#include "colors.h"

int main()
{
	{
		AAnimal* tab[4];
		// AAnimal a = new AAnimal(); //not possible because abstract

		std::cout << BOLD_PURPLE "****** CONSTRUCTION OF DOGS ******\n" RESET;
		for (int i = 0; i < 2; i++)	{
			tab[i] = new Dog();
			tab[i]->makeSound();
		}
		std::cout << "\n";
		std::cout << BOLD_PURPLE "****** CONSTRUCTION OF CATS ******\n" RESET;
		for (int i = 2; i < 4; i++)	{
			tab[i] = new Cat();
			tab[i]->makeSound();
		}
		std::cout << "\n";
		std::cout << BOLD_PURPLE"****** DESTRUCTION OF DOGS ******\n" RESET;
		for (int i = 0; i < 2; i++)	{
			delete tab[i];
		}
		std::cout << "\n";
		std::cout << BOLD_PURPLE "****** DESTRUCTION OF CATS ******\n" RESET;
		for (int i = 2; i < 4; i++)	{
			delete tab[i];
		}
	}

	return 0;
}
