#include "PhoneBook.hpp"
#include "Contact.hpp"

int main() {
	PhoneBook	phonebook;
	std::string	entered;
	std::string	index;

	std::cout << "* Welcome in my PhoneBook! *\n";
	while (entered != "EXIT") {
		std::cout << "** Please enter ADD, SEARCH or EXIT **\n";
		std::getline (std::cin, entered);
		if (std::cin.eof() == true)
				exit(1);
		if (entered == "ADD")
			phonebook.fill_contact();
		else if (entered == "SEARCH")
			phonebook.search_contact();
		else if (entered == "EXIT")
			break ;
		else if (!entered.empty())
			std::cout << "WRONG REQUEST\n";
	}
}
