#include "Contact.hpp"

Contact::Contact(void) {
	return;
}

Contact::~Contact(void) {
	return;
}

void Contact::print_info_contacts(std::string string) {

	int i = 0;

	if (string.length() > 10)
	{
		while (i < 9 && string[i]) {
			std::cout << string[i];
			i++;
		}
		std::cout << '.';
	}
	else {
		std::cout.width(10);
		std::cout << string;
	}
	std::cout << "|";
}

void Contact::print_all_contacts(int index) {

	std::cout.width(10);
	std::cout << index + 1;
	std::cout << "|";
	print_info_contacts(this->_firstname);
	print_info_contacts(this->_lastname);
	print_info_contacts(this->_nickname);
	std::cout << std::endl;
}

void Contact::print_selected_contact(void) {
	std::cout << _firstname << std::endl;
	std::cout << _lastname << std::endl;
	std::cout << _nickname << std::endl;
	std::cout << _darkest_secret << std::endl;
	std::cout << _phone_number << std::endl;
}

std::string Contact::ask_info(std::string info){

	if (info.empty()) {
		while (info.empty()) {
			if (std::cin.eof() == true)
				exit(1);
			std::cout << "Error, please enter something\n";
			std::getline (std::cin, info);
		}
	}
	return (info);
}

void Contact::add_contact(void) {

	std::cout << "Enter a first name: ";
	std::getline (std::cin, this->_firstname);
	this->_firstname = ask_info(this->_firstname);
	std::cout << "Enter a last name: ";
	std::getline (std::cin, this->_lastname);
	this->_lastname = ask_info(this->_lastname);
	std::cout << "Enter a nick name: ";
	std::getline (std::cin, this->_nickname);
	this->_nickname = ask_info(this->_nickname);
	std::cout << "Enter a darkest secret: ";
	std::getline (std::cin, this->_darkest_secret);
	this->_darkest_secret = ask_info(this->_darkest_secret);
	std::cout << "Enter a phone number: ";
	std::getline (std::cin, this->_phone_number);
	this->_phone_number = ask_info(this->_phone_number);
}