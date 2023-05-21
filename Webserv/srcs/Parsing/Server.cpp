/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:20:13 by mede-sou          #+#    #+#             */
/*   Updated: 2023/02/24 17:05:03 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "colors.h"

/****************************** INITIALISATION ********************************
******************************************************************************/

Server::Server() : body_size(5000000), autoindex(false), sublocation(false), error(false) { }

Server::Server(Server const &cpy) : methods(cpy.getMethods()), 
	port(cpy.getPort()), host(cpy.getHost()), index(cpy.getIndex()),
		error_code(cpy.getErrorCode()), error_page(cpy.getErrorPage()),
			body_size(cpy.getBodySize()), root(cpy.getRoot()), cgi_pass(cpy.getCgiPass()),
				vec_names(cpy.getName()) {
					*this = cpy;
}

Server & Server::operator=(Server const &assign) { 
	(void)assign;
	return *this; 
}

Server::~Server() {
	for (std::size_t i = 0; i < this->vec_location.size(); i++)
		delete this->vec_location[i];
	this->vec_location.clear();
 }

/********************************* UTILS **************************************
******************************************************************************/

std::string Server::cutwhitespace(std::string str)
{
	int j = str.length() - 1;
	int i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'))
		i++;
	while (str[j] && (str[j] == ' ' || str[j] == '\t' || str[j] == '\n' || str[j] == '\r'))
		j--;
	std::string new_str = str.substr(i, j - i + 1);
	return new_str;
}

std::string Server::firstword(std::string str, int i)
{
	int j = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'))
		i++;
	if (i != 0)
    	j = i;
	while (str[j] && (str[j] != ' ' && str[j] != '\t' && str[j] != '\n' && str[j] != '\r'))
		j++;
	if (str[j] == ' ' || str[j] == '\t' || str[j] == '\n' || str[j] == '\r')
		j--;
	std::string new_str = str.substr(i, j - i + 1);
	return new_str;
}

std::string Server::checksemicolon(std::string content) {
	std::size_t len = content.length() - 1;
	while (content[len] == ' ' || content[len] == '\t' || content[len] == '\n' || content[len] == '\r')
		len--;
	if (content[len] != ';')
	{
		std::cerr << "Error, semicolon missing for instruction\n";
		exit(EXIT_FAILURE);
	}
	content.erase(len, 1);
	return (content);
}

std::vector<std::string> Server::cppsplit(std::string str, char sep)
{
	int i = 0;
	int j = 0;
	std::vector<std::string> vec;
	std::string tmp;
	while (str[i] != 0)
	{
		while (str[i] != 0 && str[i] == sep)
			i++;
		j = i;
		while (str[j] != 0 && str[j] != sep)
			j++;
		if (j != i)
		{
			tmp = str.substr(i, (j - i));
			vec.push_back(tmp);
		}	
		i = j;
	}	
	return (vec);
}

std::string Server::extractcontent(std::vector<std::string>::iterator it, int i, std::string keyword)
{
	int j = 0;
	while ((*it)[j] == ' ' || (*it)[j] == '\t' || (*it)[j] == '\n' || (*it)[j] == '\r')
		j++;
	std::size_t found = (*it).find('#');
	std::string content;
	if (found != std::string::npos)
		content = (*it).substr(keyword.length() + j, 
			((*it).length() - keyword.length()) - ((*it).length() - found + 1));
	else
		content = (*it).substr(keyword.length() + j, (*it).length());
	if (i != 9)
		content = checksemicolon(content);
	return (content);
}

int Server::check_doubl_kw(std::vector<std::string> vec_kw)
{
	std::vector<std::string>::iterator it = vec_kw.begin();
	for (it = vec_kw.begin(); it != vec_kw.end(); ++it)
	{
		if (std::count(vec_kw.begin(), vec_kw.end(), *it) > 1 && (*it) != "}" && (*it) != "error_page" && (*it) != "location")
		{
			std::cerr << "Error: same field cannot be configured more than once\n";
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);

}
/********************************* GETERS *************************************
******************************************************************************/

std::string Server::getMethods() const { return (this->methods); }
std::vector<std::string> Server::getName() const { return (this->vec_names); }
std::string Server::getPort() const { return (this->port); }
std::string Server::getHost() const { return (this->host); }
std::string Server::getIndex() const { return (this->index); }
int Server::getErrorCode() const { return (this->error_code); }
std::string Server::getErrorPage() const { return (this->error_page); }
int Server::getBodySize() const { return (this->body_size); }
std::string Server::getRoot() const { return (this->root); }
bool Server::getAutoIndex() const { return (this->autoindex); }
bool Server::getError() const { return (this->error); }
std::string Server::getPathAutoIndex() const { return (this->pathAutoIndex); }
std::string Server::getCgiPass() const { return (this->cgi_pass); }
std::vector<Location *> Server::getVectorLocation() const { return (this->vec_location); }

/********************************* SETERS *************************************
******************************************************************************/

void Server::setMethods(std::string methods) { this->methods = methods; }
// void Server::setName(std::string name) { this->name = name; }
void Server::setPort(std::string port) { this->port = port; }
void Server::setHost(std::string host) { this->host = host; }
void Server::setIndex(std::string index) {
	this->index = this->root + "/" + index;
}

void Server::setErrorCode(int error_code) { this->error_code = error_code; }
void Server::setErrorPage(std::string error_page) { this->error_page = error_page; }
void Server::setBodySize(int body_size) { this->body_size = body_size; }
void Server::setRoot(std::string root) { this->root = root; }
void Server::setError(bool error) { this->error = error; }
void Server::setCgiPass(std::string cgi_pass) { this->cgi_pass = cgi_pass; }

void Server::setAutoIndex(std::string autoindex) {
	std::string pathAutoIndex;
	if (autoindex == "on")
	{
		this->autoindex = true;
		pathAutoIndex = this->root;
	}
	else
		pathAutoIndex = "";
	this->pathAutoIndex = pathAutoIndex;
}

/******************************* CHECK ERRORS *********************************
******************************************************************************/

int Server::check_server_name() { 
	tmp = cppsplit(_content, ' ');
	for (size_t i = 0; i < tmp.size(); i++)
	{
		if (tmp[i].find(':') != std::string::npos)
		{
			std::cerr << "Error: server name cannot contain port\n";
			return (tmp.clear(), EXIT_FAILURE);
		}
		else
			vec_names.push_back(tmp[i]);
	}
	return (tmp.clear(), EXIT_SUCCESS);
}
 

int Server::check_listen() { 	
	
	tmp = cppsplit(_content, ':');
	if (tmp.size() == 2)
	{
		setHost(tmp[0]);
		setPort(tmp[1]);
	}
	else 
	{
		int count_p = 0;
		bool is_digit = true;
		for (int j = 0; _content[j]; j++)
		{
			if (_content[j] == '.')
				count_p++;
			else if (!isdigit(_content[j]))
				is_digit = false;
		}
		if (count_p == 3)
			setHost(_content);
		else if (is_digit == true)
			setPort(_content);
		else if (count_p != 3 && is_digit == false)
		{
			std::cerr << "Error: listen has to be a port or an ip\n";
			return (tmp.clear(), EXIT_FAILURE);
		}
	}
	return (tmp.clear(), EXIT_SUCCESS);
}

int Server::check_root() {
	tmp = cppsplit(_content, ' ');
	if (tmp.size() > 1)
	{
		std::cerr << "Error, root has to be a single file\n";
		return (tmp.clear(), EXIT_FAILURE);
	}
	setRoot(_content);
	return (tmp.clear(), EXIT_SUCCESS);
}

int Server::check_index() {
	tmp = cppsplit(_content, ' ');
	if (tmp.size() > 1)
	{
		std::cerr << "Error, index has to be a single file\n";
		return (tmp.clear(), EXIT_FAILURE);
	}
	setIndex(_content);
	return (tmp.clear(), EXIT_SUCCESS);
}

int Server::check_auto_index() {
	if (_content.compare("on") != 0 && _content.compare("off") != 0)
	{			
		std::cerr << "Error, autoindex has to be either on or off\n";
		return (EXIT_FAILURE);
	}
	setAutoIndex(_content);
	return (EXIT_SUCCESS);
}

int Server::check_error_page() {
	tmp = cppsplit(_content, ' ');

	if (tmp.size() > 2)
	{
		std::cerr << "Error, error_page has to be a single file\n";
		return (tmp.clear(), EXIT_FAILURE);
	}
	if (atoi(tmp[0].c_str()) < 400 || atoi(tmp[0].c_str()) > 599)
	{
		std::cerr << "Error, error code has to be between 400 et 599\n";
		return (tmp.clear(), EXIT_FAILURE);
	}
	if (tmp[0] == "404")
		setErrorPage(tmp[1]);
	return (tmp.clear(), EXIT_SUCCESS);

}

int Server::check_allow_methods() {
	tmp = cppsplit(_content, ' ');

	
	if (tmp.size() > 3)
	{			
		std::cerr << "Error, method is not allowed\n";
		return (tmp.clear(), EXIT_FAILURE);
	}

	std::string new_content;
	std::vector<std::string>::iterator it = tmp.begin();
	for (; it != tmp.end() ; ++it)
	{
		if ((*it).compare("GET") == 0 || (*it).compare("POST") == 0 || (*it).compare("DELETE") == 0)
			new_content += (*it) + ' '; 
		else
		{			
			std::cerr << "Error, method is not allowed\n";
			return (tmp.clear(), EXIT_FAILURE);
		}
	}
	setMethods(new_content);
	return (tmp.clear(), EXIT_SUCCESS);

}

int Server::check_client_max_body_size() {
	std::string cut = firstword(_content, 0);
	int size = 1000000;

	for (unsigned long int i = 0; i < _content.length() - 2 && cut[i]; i++) {
		if (!isdigit(cut[i]) && cut[i] != ' ' && cut[i] != '\t' && cut[i] != '\n' && cut[i] != '\r')
		{			
			std::cerr << "Error, wrong body size format\n";
			return (EXIT_FAILURE);
		}
	}
	if (_content[_content.length() - 1] != 'm' && _content[_content.length() - 1] != 'M')
	{			
		if (!isdigit(_content[_content.length() - 1]))
		{
			std::cerr << "Error, wrong body size format\n";
			return (EXIT_FAILURE);
		}
		size = atoi(cut.c_str());
	}
	else if (_content[_content.length() - 1] == 'm' || _content[_content.length() - 1] == 'M')
	{
		size = atoi(cut.c_str());
		size *= 1000000;
	}
	if (size > 50000000)
	{
		std::cerr << "Error, max body size too big. Using default value: 5MB\n";
		setBodySize(5000000);
		return (EXIT_SUCCESS);
	}
	setBodySize(size);
	return (EXIT_SUCCESS);

}

void Server::check_cgi_pass() {
	setCgiPass(_content);
}

int Server::check_each_element(std::string content, int i)
{
	_content = cutwhitespace(content);
	if (i == 0)
	{
		if (check_server_name() == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (i == 1)
	{
		if (check_listen() == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (i == 2)
	{
		if (check_root() == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (i == 3)
	{
		if (check_index() == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (i == 4)
	{
		if (check_allow_methods() == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (i == 5)
	{
		if (check_error_page() == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (i == 6)
	{
		if (check_client_max_body_size() == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (i == 7)
	{
		if (check_auto_index() == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (i == 8)
		check_cgi_pass();
	return (EXIT_SUCCESS);
}


/**************************** CREATE LOCATION *********************************
******************************************************************************/

void Server::copy_server_to_location(Location &location) {
	if (vec_location.size() == 0 || sublocation == false)
	{
		location.setHost(this->getHost());
		location.setPort(this->getPort());
		location.setMethods(this->getMethods());
		location.setRoot(this->getRoot());
		// location.setIndex(this->getIndex());
		location.setAutoIndex("off");
		location.setErrorPage(this->getErrorPage());
		location.setErrorCode(this->getErrorCode());
		location.setBodySize(this->getBodySize());
		location.setCgiPass(this->getCgiPass());
	}
	else
	{
		std::vector<Location *>::iterator ite = vec_location.end();
		--ite;
		location.setHost((*ite)->getHost());
		location.setPort((*ite)->getPort());
		location.setMethods((*ite)->getMethods());
		location.setRoot((*ite)->getRoot());
		// location.setIndex((*ite)->getIndex());
		location.setAutoIndex("off");
		location.setErrorPage((*ite)->getErrorPage());
		location.setErrorCode((*ite)->getErrorCode());
		location.setBodySize((*ite)->getBodySize());
		location.setCgiPass((*ite)->getCgiPass());
	}
}

void Server::makeDefaultLocation()
{
	Location* location = new Location();
	copy_server_to_location(*location);
	location->setIndex(this->getIndex());
	location->setName("/");
	vec_location.push_back(location);
}

std::vector<std::string>::iterator Server::createNewLocation(std::vector<std::string>::iterator it) {
	const std::string tab[8] = {"listen", "root", "index", "allow_methods",
		"error_page", "client_max_body_size", "autoindex", "cgi_pass"};
	Location* location = new Location();
	std::vector<std::string> vec_kw;
	std::vector<std::string>::iterator tmp_it  = it;
	
	copy_server_to_location(*location);
	if (location->check_each_element(extractcontent(it, 9, "location"), 9) == EXIT_FAILURE)
		return (error = true, delete location, it);
	for (; it != vec_file.end(); ++it)
	{
		std::string keyword = firstword(*it, 0);

		if (keyword.compare("location") == 0 && tmp_it != it)
		{
			sublocation = true;
			break;
		}
		for (int i = 0; i < 8; i++)
		{
			if (!keyword.empty() && keyword.compare(tab[i]) == 0)
			{
				if (location->check_each_element(extractcontent(it, i, keyword), i) == EXIT_FAILURE)
					return (error = true, delete location, it);
				vec_kw.push_back(keyword);
				break ;
			}
			else if (i == 7 && !keyword.empty() && keyword.compare("location") != 0 
				&& keyword.compare("server") != 0 && keyword.compare("}") != 0
					&& keyword.compare("#") != 0)
			{
				std::cerr << "Error file: wrong keyword\n";
				return (error = true, delete location, it);
			}
		}
		if (keyword.compare("}") == 0)
		{
			sublocation = false;
			break;
		}
	}
	if (location->getIndex().empty())
		location->setIndex(this->getIndex());
	if (check_doubl_kw(vec_kw) == EXIT_FAILURE)
		return (error = true, delete location, it);
	vec_location.push_back(location);
	count_location++;
	if (sublocation == true)
		it--;
	return (it);

}

/******************************** PRINT ***************************************
******************************************************************************/

void Server::printServer()
{
	std::cout << "name: " << name << "\n";
	std::cout << "host: " << host << "\n";
	std::cout << "port: " << port << "\n";
	std::cout << "methods: " << methods << "\n";
	std::cout << "root: " << root << "\n";
	std::cout << "index: " << index << "\n";
	std::cout << "autoindex: " << autoindex << "\n";
	std::cout << "path autoindex: " << pathAutoIndex << "\n";
	std::cout << "error_page: " << error_page << "\n";
	std::cout << "cgi_pass: " << cgi_pass << "\n";
	std::cout << "body_size: " << body_size << "\n\n";
}

void Server::printLocationVector() {
	std::vector<Location *>::iterator it;
	std::cout << "CE SERVEUR POSSEDE " << vec_location.size() << " LOCATION\n";
	
		for (it = vec_location.begin(); it != vec_location.end(); ++it)
		{
			(*it)->printLocation();
		}
}
