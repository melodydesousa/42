#ifndef PHONEBOOK_H
# define PHONEBOOK_H

# include <iostream>
# include <string>
# include <cctype>
# include <stdlib.h>
# include "Contact.hpp"

class PhoneBook {

public:

	PhoneBook(void);
	~PhoneBook(void);

	void	search_contact(void);
	void	fill_contact(void);

private:
	int		_index;
	int		_total;
	Contact	_contact[8];
};


#endif
