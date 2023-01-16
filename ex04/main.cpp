#include <string>
#include <iostream>
#include <fstream>

int main(int ac, char **av) 
{
	std::string line;
	std::string	new_file = ".replace";
	
	if (ac != 4)
		std::cout << "Error: wrong number of arguments\n";

	std::ifstream file (av[1]);
	std::string s1 = av[2];
	std::string s2 = av[3];
	new_file = av[1] + new_file;

	if (!file.is_open())
		std::cout << "Error: cannot open file\n";
	else
	{
		std::ofstream file2(new_file.c_str());
		while (std::getline (file, line))
		{
			std::size_t found = line.find(s1);
			if (found!= std::string::npos)
			{
				line.erase(found, s1.length());
				line.insert(found, s2);
			}
			file2 << line << std::endl;
		}
	}
	file.close();
	return 0;
}

// https://cplusplus.com/reference/string/string/replace/
//substr insert erase