#ifndef CONTACT_H
# define CONTACT_H

# include <iostream>
# include <string>
# include <cctype>
# include <stdlib.h>

class	Contact {

public:
	
	Contact(void);
	~Contact(void);
	
	std::string	ask_info(std::string info);
	void		add_contact(void);
	void		print_all_contacts(int index);
	void		print_info_contacts(std::string);
	void		print_selected_contact(void);

private:
	std::string _firstname;
	std::string _lastname;
	std::string _nickname;
	std::string _darkest_secret;
	std::string	_phone_number;
};

#endif