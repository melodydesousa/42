#include <string>
#include <iostream>
#include <fstream>

int main(int ac, char **av) 
{
	std::string line;
	std::string	new_file = ".replace";
	std::size_t pos = 0;

	if (ac != 4)
		return (std::cout << "Error: wrong number of arguments\n", 1);

	std::ifstream file (av[1]);
	std::string s1 = av[2];
	std::string s2 = av[3];
	new_file = av[1] + new_file;

	if (!file.is_open())
		return (std::cout << "Error opening file\n", 1);
	else
	{
		std::ofstream file2(new_file.c_str());
		
		if (!file2.is_open())
			return (std::cout << "Error opening file\n", 1);

		std::size_t found = line.find(s1, pos);

		while (std::getline (file, line))
		{
			while ((found = line.find(s1, pos)) != std::string::npos)
			{
				line.erase(found, s1.length());
				line.insert(found, s2);
				pos = found + s2.length();
			}
			if (found == std::string::npos)
			{
				found = 0;
				pos = 0;
			}
			file2 << line << std::endl;
		}
		file2.close();
	}
	file.close();
	return 0;
}
