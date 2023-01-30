#include "Animal.hpp"
#include "WrongAnimal.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"
#include "Dog.hpp"
#include "colors.h"

int main()
{
	std::cout << BOLD_CYAN "******************** ANIMAL ********************\n" RESET; 
	const Animal* meta = new Animal();
	const Animal* dog = new Dog();
	const Animal* cat = new Cat();
	std::cout << "\n";
	std::cout << "type of dog = " << dog->getType() << " " << "\n";
	std::cout << "type of cat = " << cat->getType() << " " << "\n";
	std::cout << "type of animal = " << meta->getType() << " " << "\n\n";
	std::cout << "cat sound = " ;
	cat->makeSound(); //will output the cat sound!
	std::cout << "dog sound = ";
	dog->makeSound();
	std::cout << "animal sound = ";
	meta->makeSound();
	std::cout << "\n";

	delete meta;
	delete dog;
	delete cat;
	std::cout << "\n";

	std::cout << BOLD_CYAN "**************** WRONG ANIMAL *****************\n" RESET; 


	const  WrongAnimal* wronganimal = new WrongAnimal();
	const WrongAnimal* wrongcat = new WrongCat();
	std::cout << "\n";
	std::cout << "type of cat = " << wrongcat->getType() << " " << "\n";
	std::cout << "type of animal = " << wronganimal->getType() << " " << "\n\n";

	std::cout << "cat sound = " ;
	wrongcat->makeSound(); //will output the cat sound!
	std::cout << "animal sound = ";
	wronganimal->makeSound();
	std::cout << "\n";

	delete wronganimal;
	delete wrongcat;
	
	return 0;
}