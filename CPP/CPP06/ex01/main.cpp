#include "Data.hpp"

int main()
{
	Data data;
	Data* ptr = &data;

	std::cout << "i = " << data.i << "\n";
	std::cout << "test = " << data.test << "\n";
	std::cout << "ptr (data's address) = " << ptr << "\n";

	uintptr_t raw = data.serialize(ptr);
	std::cout << "*SERIALIZE*\nraw (unsigned int ptr) = " << raw << "\n";
	
	ptr = data.deserialize(raw);
	std::cout << "*DESERIALIZE*\nptr (data's address) = " << ptr << "\n";
	std::cout << "i = " << data.i << "\n";
	std::cout << "test = " << data.test << "\n";

	return 0;
}
