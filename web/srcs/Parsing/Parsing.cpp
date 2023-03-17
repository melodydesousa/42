/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:49:20 by mede-sou          #+#    #+#             */
/*   Updated: 2023/03/16 17:35:30 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing.hpp"
#include "colors.h"

/****************************** INITIALISATION ********************************
******************************************************************************/

Parsing::Parsing() : count_server(0) { }

Parsing::~Parsing() { 
	std::cout << "PARSING DESTRUCTOR\n";
	for (std::size_t i = 0; i < this->vec_server.size(); i++)
		delete this->vec_server[i];
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

void Parsing::init_conf_file(std::string file)
{
    if (file.empty() == 1)
		file = "conf_file.conf";
	std::size_t found = file.rfind(".conf");
	try
	{
   		if (found != file.size() - 5)
    	    throw WrongArguments ();
  	}
	catch (std::exception &e) { }
	std::ifstream file_tmp(file.c_str());
    try
	{
    	if (!file_tmp.is_open())
       		throw ErrorFile ();
	}
    catch (std::exception &e)  	{ }
    std::string line;

    while (std::getline (file_tmp, line, '\n'))
    {
       this->vec.push_back(line.c_str());
    }
    file_tmp.close();
    check_brackets(this->vec);
    setVecServer();
	CleanServer();
	makeListPort();
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
				vec_server.erase(it);
				it = it_be;
			}
			it++;
		}
		it_be++;
	}
}

void Parsing::setVecServer()
{
	for (this->it = this->vec.begin(); this->it != this->vec.end(); ++this->it)
	{
		if (!(*this->it).empty())
		{
			std::string new_str = first_word(*this->it, 0);
			if (new_str.compare("server") == 0)
			{
				if (check_syntax(this->it, "server") == true)
				{
                    count_server++;
					vec_server.push_back(createNewServer(this->it));
                }
				else
				{
					std::cerr << "Error: Syntax or brackets missing\n";
					exit(EXIT_FAILURE);
				}
			}
			else 
			{
				if ((new_str[0] != '#' && new_str[0] != '\0') && count_server == 0)
				{
					std::cerr << "Error file: keyword not accepted\n";
					exit(EXIT_FAILURE);
				}
				else if (it == this->vec.end() && count_server == 0)
				{
					std::cerr << "Error file: missing server keyword\n";
					exit(EXIT_FAILURE);
				}
			}
		}
	}
}

Server* Parsing::createNewServer(std::vector<std::string>::iterator it)
{
	const std::string tab[9] = {"server_name", "listen", "root", "index", "allow_methods",
		"error_page", "client_max_body_size", "autoindex", "cgi_pass"};
	Server* server = new Server();
	std::vector<std::string>::iterator tmp_it = it;
	std::vector<std::string> vector_kw;

	server->vec_file = this->vec;
	
	for (; it != this->vec.end(); ++it)
	{
		std::string keyword = first_word(*it, 0);
		if (keyword.compare("location") == 0)
			it = server->createNewLocation(it);
		for (int i = 0; i < 9; i++)
		{
			if (!keyword.empty() && keyword.compare(tab[i]) == 0)
			{
				int j = 0;
				while ((*it)[j] == ' ' || (*it)[j] == '\t')
					j++;
				std::size_t found = (*it).find('#');
				std::string content;
				if (found != std::string::npos)
					content = (*it).substr(keyword.length() + j,
						((*it).length() - keyword.length()) - ((*it).length() - found + 1));
				else
					content = (*it).substr(keyword.length() + j, (*it).length());
				content = check_semicolon(content);
				server->check_each_element(content, i);
				vector_kw.push_back(keyword);
				break;
			}
			else if (i == 8 && !keyword.empty() && keyword.compare("location") != 0 
				&& keyword.compare("server") != 0 && keyword.compare("}") != 0
					&& keyword.compare("#") != 0)
			{
				std::cerr << "Error file: wrong keyword\n";
				exit(EXIT_FAILURE);
			}
		}
		if (keyword.compare("server") == 0 && it != tmp_it)
			break;
	}
	check_doublon_kw(vector_kw);
	return (server);
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
