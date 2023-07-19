#ifndef DATA_H
# define DATA_H

# include <iostream>
# include <stdexcept>
# include <cstring>
# include <stdint.h>

class	Data {
public:
	Data(void);
	~Data(void);
	Data& operator=(Data const &assign);
	Data(Data const &cpy);

	uintptr_t serialize(Data* ptr);
	Data* deserialize(uintptr_t raw);

	int i;
	std::string test;

};

#endif
