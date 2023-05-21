/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfontain <cfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:49:20 by mede-sou          #+#    #+#             */
/*   Updated: 2023/03/29 12:50:22 by cfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing.hpp"
#include "colors.h"

/****************************** INITIALISATION ********************************
******************************************************************************/

Parsing::Parsing() : count_server(0) { }

Parsing::~Parsing() { 
	for (std::size_t i = 0; i < this->vec_server.size(); i++)
	{
		delete this->vec_server[i];
	}
	this->vec_server.clear();
}

Parsing::Parsing(Parsing const &cpy) : vec(cpy.vec), it(cpy.it),
	vec_server(cpy.vec_server), count_server(cpy.count_server) {
		*this = cpy;
}

Parsing & Parsing::operator=(Parsing const &assign) { 
	this->vec = assign.vec;
    this->it = assign.it;
    this->vec_server = assign.vec_server;
    this->count_server = assign.count_server;
    return *this;
}

int Parsing::init_conf_file(std::string file)
{
    if (file.empty() == 1)
	{
		std::cout << "Error: Configuration file is missing. Using default configuration file\n";
		file = "default.conf";
	}
	else 
	{
		std::size_t found = file.rfind(".conf");
		if (found != file.size() - 5)
		{
			std::cout << "Error: Cannot open file. Using default configuration file\n";
			file = "default.conf";
		}
	}
	std::ifstream file_tmp(file.c_str());
	if (!file_tmp.is_open())
    {
		std::cout << "Error: Cannot open file. Using default configuration file\n";
		file = "default.conf";
	    file_tmp.close();
		std::string line;
		std::ifstream file_tmp2(file.c_str());
		while (std::getline (file_tmp2, line, '\n'))
		{
			this->vec.push_back(line.c_str());
		}
		file_tmp2.close();
	}
	else
	{	
		std::string line;
		std::getline (file_tmp, line);
		if (line.empty())
		{
			std::cout << "Error: Cannot open file. Using default configuration file\n";
			file = "default.conf";
			file_tmp.close();
			std::string line;
			std::ifstream file_tmp2(file.c_str());
			while (std::getline (file_tmp2, line, '\n'))
			{
				this->vec.push_back(line.c_str());
			}
			file_tmp2.close();
		}
		else
		{
			this->vec.push_back(line.c_str());
			while (std::getline (file_tmp, line, '\n'))
			{
				this->vec.push_back(line.c_str());
			}
			file_tmp.close();
		}
	}
    if (check_brackets(this->vec) == EXIT_FAILURE)
		return EXIT_FAILURE;
    if (setVecServer() == EXIT_FAILURE)
		return EXIT_FAILURE;
	CleanServer();
	makeListPort();
	return EXIT_SUCCESS;
	// printVector();
}

/********************************* GETTERS ************************************
******************************************************************************/
int Parsing::getCountServer() {return(this->count_server);}

std::vector<Server *> Parsing::getVectorServer() { return (this->vec_server); }

std::string Parsing::get_file(void) const {	return(this->file);}

std::vector<std::string> Parsing::getListPort() { return (this->list_port); }

/********************************* SETTERS ************************************
******************************************************************************/

void	Parsing::set_file(std::string file) { this->file = file; }

/**************************** CREATE SERVERS **********************************
******************************************************************************/

void Parsing::makeListPort() 
{
	std::vector<Server*>::iterator it = this->vec_server.begin();	
	for (; it != this->vec_server.end(); ++it)
	{
		this->list_port.push_back((*it)->getPort());
	}
}

void Parsing::CleanServer()
{
	std::vector<Server*>::iterator it_be = this->vec_server.begin();
	std::vector<Server*>::iterator it;
	
	while (it_be != this->vec_server.end())
	{
		it = it_be + 1;
		while (it != this->vec_server.end())
		{
			if ((*it)->getPort().compare((*it_be)->getPort()) == 0)
			{
				Server *tmp = *it;
				delete tmp;
				vec_server.erase(it);
				it = it_be;
			}
			it++;
		}
		it_be++;
	}
}

int Parsing::setVecServer()
{
	for (this->it = this->vec.begin(); this->it != this->vec.end(); ++this->it)
	{
		if (!(*this->it).empty())
		{
			str = first_word(*this->it, 0);
			if (str.compare("server") == 0)
			{
				if (check_syntax(this->it, "server") == true)
				{
                    count_server++;
					this->it++;
					if (createNewServer(this->it) == EXIT_FAILURE)
						return (EXIT_FAILURE);
                }
				else
				{
					std::cerr << "Error: Syntax or brackets missing\n";
					return (EXIT_FAILURE);
				}
			}
			else 
			{
				if ((str[0] != '#' && str[0] != '\0') && count_server == 0)
				{
					std::cerr << "Error file: keyword not accepted\n";
					return (EXIT_FAILURE);
				}
				else if (it == this->vec.end() && count_server == 0)
				{
					std::cerr << "Error file: missing server keyword\n";
					return (EXIT_FAILURE);
				}
			}
		}
	}
	return (EXIT_SUCCESS);
}

int Parsing::createNewServer(std::vector<std::string>::iterator it)
{
	const std::string tab[9] = {"server_name", "listen", "root", "index", "allow_methods",
		"error_page", "client_max_body_size", "autoindex", "cgi_pass"};
	Server* server = new Server();
	tmp_it = it;

    std::vector<std::string> vector_kw;
	server->vec_file = this->vec;
	
	for (; it != this->vec.end(); ++it)
	{
		keyword = first_word(*it, 0);
		if (keyword.compare("location") == 0)
			it = server->createNewLocation(it);
		if (server->getError() == true)
			return (delete server, EXIT_FAILURE);
		for (int i = 0; i < 9; i++)
		{
			if (!keyword.empty() && keyword.compare(tab[i]) == 0)
			{
				int j = 0;
				while ((*it)[j] == ' ' || (*it)[j] == '\t')
					j++;
				std::size_t found = (*it).find('#');
				
				if (found != std::string::npos)
					content = (*it).substr(keyword.length() + j,
						((*it).length() - keyword.length()) - ((*it).length() - found + 1));
				else
					content = (*it).substr(keyword.length() + j, (*it).length());				
				content = check_semicolon(content);
				if (content == "")
					return (delete server, EXIT_FAILURE);
				if (server->check_each_element(content, i) == EXIT_FAILURE)
					return (delete server, EXIT_FAILURE);
				vector_kw.push_back(keyword);
				break;
			}
			else if (i == 8 && !keyword.empty() && keyword.compare("location") != 0 
				&& keyword.compare("server") != 0 && keyword.compare("}") != 0
					&& keyword.compare("#") != 0)
			{
				std::cerr << "Error file: wrong keyword\n";
				return (delete server, EXIT_FAILURE);
			}
		}
		if (keyword.compare("server") == 0 && it != tmp_it)
			break;
	}
	if (check_doublon_kw(vector_kw) == EXIT_FAILURE)
		return (delete server, EXIT_FAILURE);
	if (server->getVectorLocation().empty())
		server->makeDefaultLocation();
	vec_server.push_back(server);
	return EXIT_SUCCESS;
}

/******************************** PRINT ***************************************
******************************************************************************/

void Parsing::printVector() {
	std::vector<Server *>::iterator it;
	std::cout << "LE FICHIER DE CONFIG POSSEDE " << vec_server.size() << " SERVEUR\n";
	
		for (it = vec_server.begin(); it != vec_server.end(); ++it)
		{
			std::cout << "\n**************************************\n";
			std::cout << "*************** SERVER ***************\n";
			std::cout << "**************************************\n";
			(*it)->printServer();
			std::cout << "---------------------------------------\n";
			std::cout << "-------- LOCATION de ce serveur -------\n";
			std::cout << "---------------------------------------\n";
			(*it)->printLocationVector();
		}
}
