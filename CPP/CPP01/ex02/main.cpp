#include <iostream>
#include <string>

int main(){
	std::string brain("HI THIS IS BRAIN");
	std::string* stringPTR = &brain;
	std::string& stringREF = brain;

	std::cout << "string address: " << &brain << std::endl;
	std::cout << "stringPTR address: " << stringPTR << std::endl;
	std::cout << "stringREF address: " << &stringREF << "\n" << std::endl;

  stringREF = "lol";
	std::cout << "string value: " << brain << std::endl;
	std::cout << "stringPTR value: " << *stringPTR << std::endl;
	std::cout << "stringREF value: " << stringREF << std::endl;
	return 0;
}
