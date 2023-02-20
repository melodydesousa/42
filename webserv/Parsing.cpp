/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:20:13 by mede-sou          #+#    #+#             */
/*   Updated: 2023/02/20 16:18:25 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing.hpp"

void print_vec(std::vector<std::string> vec)
{
    std::vector<std::string>::iterator it = vec.begin();
    for (it = vec.begin(); it != vec.end(); ++it)
    {
        std::cout << *it << "\n";
    }
}

void check_accolades(std::vector<std::string> vec)
{
	std::vector<std::string>::iterator it = vec.begin();
	int count = 0; int count2 = 0;
	for (it = vec.begin(); it != vec.end();++it)
	{
		if (!(*it).empty())
		{
			std::size_t finding = (*it).find("{");
			std::size_t finding2 = (*it).find("}");
			if (finding != std::string::npos)
				count++;
			else if (finding2 != std::string::npos)
				count2++;
		}
	}
	try 
	{
		if ((count + count2) % 2 != 0)
			throw WrongFile ();
	}
    catch (std::exception &e) {std::cout << e.what();}
}

std::vector<std::string>::iterator check_if_empty_or_comments(std::vector<std::string> vec, std::string to_compare)
{
	std::vector<std::string>::iterator it = vec.begin();
    try 
	{
    	while ((*it).compare(to_compare) != 0 && it != vec.end())
		{
			if ((*it).empty())
				++it;
			std::size_t found = (*it).find("#");
			std::size_t found2 = (*it).find_first_not_of(" ");
			if (found == 0)
				++it;
			else if (found2 != std::string::npos)
				throw WrongFile ();
			else 
				++it;
			if (it == vec.end())
				throw WrongFile ();
		}
    	// print_vec(vec);
    }
    catch (std::exception &e) {std::cout << e.what();}
	return (it);
}

void check_config_file(std::vector<std::string> vec)
{
    check_accolades(vec);
	std::vector<std::string>::iterator it = check_if_empty_or_comments(vec, "server {");
	std::string tab[7] = {"server_name", "location", "listen", "root", "index", "allow_methods", "cgi_pass"};
}

void init_conf_file(std::string file)
{
    std::size_t found = file.rfind(".conf");
    if (found != file.size() - 5)
        throw WrongArguments ();
    std::ifstream file_tmp(file);
    if (!file_tmp.is_open())
       throw ErrorFile ();
       
    std::vector<std::string> Elem;
    std::string line;
    std::vector<std::string>::iterator it;

    while (std::getline (file_tmp, line, '\n'))
    {
        Elem.push_back(line.c_str());
    }
    check_config_file(Elem);
}

int main(int ac, char **av)
{
    if (ac != 2)
        return (std::cout << "Wrong number of arguments\n", 1);
    std::string file = av[1];
    init_conf_file(file);
    
}