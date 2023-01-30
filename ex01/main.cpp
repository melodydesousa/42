#include "Animal.hpp"
#include "WrongAnimal.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"
#include "Dog.hpp"
#include "Brain.hpp"
#include "colors.h"

int main()
{
	// {
	// 	std::cout << BOLD_YELLOW"********** MEMORY CHECK **********\n" RESET;
	// 	const Animal* j = new Dog();
	// 	const Animal* i = new Cat();
	// 	std::cout << "\n";
	// 	delete j;//should not create a leak
	// 	delete i;
	// }

	{
		std::cout << "\n";
		std::cout << BOLD_YELLOW "************ DEEP COPY ************\n" RESET; 
		const Dog* dog = new Dog();
		std::cout << "\n";
		
		std::cout << "Dog's idea #1 = " << dog->getBrain()->getIdea(1) << "\n";
		std::cout << "Dog's idea #2 = " << dog->getBrain()->getIdea(2) << "\n\n";
		dog->getBrain()->setIdeas(1, "I want to eat");
		std::cout << "new Dog's idea #1 = " << dog->getBrain()->getIdea(1) << "\n";

		std::cout << BOLD_YELLOW"\n********** DELETE DOG *************\n" RESET;
		const Dog* dogcopy = new Dog(*dog);
		std::cout << "\n";
		delete dog;
		std::cout << "\n";
		std::cout << "DogCopy's idea #1 = " << dogcopy->getBrain()->getIdea(1) << "\n";
		std::cout << "DogCopy's idea #2 = " << dogcopy->getBrain()->getIdea(2) << "\n\n";
		dogcopy->getBrain()->setIdeas(1, "I want to pee");
		std::cout << "new DogCopy's idea #1 = " << dogcopy->getBrain()->getIdea(1) << "\n\n";

		delete dogcopy;
	}
	
	// {
	// 	Animal* tab[4];

	// 	std::cout << "****** CONSTRUCTION OF DOGS ******\n";
	// 	for (int i = 0; i < 2; i++)	{
	// 		tab[i] = new Dog();
	// 		tab[i]->makeSound();
	// 	}
	// 	std::cout << "\n";
	// 	std::cout << "****** CONSTRUCTION OF CATS ******\n";
	// 	for (int i = 2; i < 4; i++)	{
	// 		tab[i] = new Cat();
	// 		tab[i]->makeSound();
	// 	}
	// 	std::cout << "\n";
	// 	std::cout << "****** DESTRUCTION OF DOGS ******\n";
	// 	for (int i = 0; i < 2; i++)	{
	// 		delete tab[i];
	// 	}
	// 	std::cout << "\n";
	// 	std::cout << "****** DESTRUCTION OF CATS ******\n";
	// 	for (int i = 2; i < 4; i++)	{
	// 		delete tab[i];
		// std::cout << "\n";
	// 	}
	// }
	return 0;
}

// deep copy needed if object is dynamically allocated like Brain - each one has a new brain