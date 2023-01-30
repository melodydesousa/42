#include "PhoneBook.hpp"

PhoneBook::PhoneBook(void) {
	this->_index = 0;
	this->_total = 0;
	return;
}

PhoneBook::~PhoneBook(void){
	return;
}

void PhoneBook::fill_contact(void) {

	if (this->_index == 8)
		this->_index = 0;
	this->_contact[this->_index].add_contact();
	if (this->_total < 8)
		this->_total++;
	this->_index++;
	return;
}

void PhoneBook::search_contact(void) {
	int 		i = 0;
	int			index;
	std::string index_entered;

	if (this->_total == 0) {
		std::cout << "You need to add contacts first\n";
		return ;
	}
	std::cout.width(10);
	std::cout << "index" << "|";
	std::cout.width(10);
	std::cout << "first name" << "|";
	std::cout.width(10);
	std::cout << "last name" << "|";
	std::cout.width(10);
	std::cout << "nickname" << "|\n";
	while (i < this->_total) {
		this->_contact[i].print_all_contacts(i);
		i++;
	}
	std::cout << "Please enter an index: ";
	std::getline (std::cin, index_entered);
	index = atoi(index_entered.c_str());
	while (index > this->_total || (index <= 0 || index > 8)) {
		if (std::cin.eof() == true)
			exit(1);
		if (index > this->_total)
			std::cout << "The contact doesn't exist yet\n";
		else if (index <= 0 || index > 8)
			std::cout << "Invalid index, must be between 1 and 8\n";
		std::cout << "Please enter a valid index: ";
		std::getline (std::cin, index_entered);
		index = atoi(index_entered.c_str());
	}	
	this->_contact[index - 1].print_selected_contact();
}
