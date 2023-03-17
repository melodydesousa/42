/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:24:03 by amanasse          #+#    #+#             */
/*   Updated: 2023/03/16 17:38:40 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgi.hpp"
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>


//////////////////////////////////////////////////////
//                                                  //
//                    Constructors                  //
//                                                  //
//////////////////////////////////////////////////////


Cgi::Cgi(void)
{
	this->_img = false;
	this->_Favicon = false;
	this->_AutoIndex = false;
	this->_img_to_Html = NULL;
	this->_env_cgi = NULL;
    return;
}

Cgi::~Cgi(void)
{
	this->ClearArray();
    return;
}

//////////////////////////////////////////////////////
//                                                  //
//                FONCTONS MEMBRES                  //
//                                                  //
//////////////////////////////////////////////////////

void Cgi::DeleteMethod(void)
{
	
}


//////////////////////////////////////////////////////
//                                                  //
//                CONVERSION HTML                   //
//                                                  //
//////////////////////////////////////////////////////

std::string Cgi::html_to_string(std::string value_error)
{
	std::string		line;
	std::string		content;
	if (value_error == "200 OK")
	{
		std::map<std::string, std::string> 	envMap = this->getMap();
		std::string 						value = this->getPathInfo();
		std::ifstream						file(value.c_str());

		if (file.is_open() == true)
		{
			while (getline(file, line))
			{
				content += line + "\n";
			}
			file.close();
		}
		else
		{
			std::cout << "ERROR\nCannot open" << std::endl;
		}
		return (content);
	}
	if (value_error == "200 AUTO")
	{
		std::map<std::string, std::string> 	envMap = this->getMap();
		std::string 						value = this->_PathInfo + "autoindex.html";
		std::cout << BLUE << value << RESET << std::endl;
		std::ifstream						file(value.c_str());
		
		if (file.is_open() == true)
		{
			while (getline(file, line))
			{
				content += line + "\n";
			}
			file.close();
		}
		else
		{
			std::cout << "ERROR\nCannot open" << std::endl;
		}
		return (content);
	}
	else if (value_error == "404")
	{
		std::string 			value = "./srcs/CGI/errors/404.html";
		std::ifstream			file(value.c_str());
		if (file.is_open() == true)
		{
			while (getline(file, line))
			{
				content += line + "\n";
			}
			file.close();
		}
		else
		{
			std::cout << "ERROR\nCannot open" << std::endl;
		}
		return (content);
	}
	else if (value_error == "400")
	{
		std::string 			value = "./srcs/CGI/errors/400.html";
		std::ifstream			file(value.c_str());
		if (file.is_open() == true)
		{
			while (getline(file, line))
			{
				content += line + "\n";
			}
			file.close();
		}
		else
		{
			std::cout << "ERROR\nCannot open" << std::endl;
		}
		return (content);
	}
	else if (value_error == "405")
	{
		std::string 			value = "./srcs/CGI/errors/405.html";
		std::ifstream			file(value.c_str());
		if (file.is_open() == true)
		{
			while (getline(file, line))
			{
				content += line + "\n";
			}
			file.close();
		}
		else
		{
			std::cout << "ERROR\nCannot open" << std::endl;
		}
		return (content);
	}
	else if (value_error == "409")
	{
		std::string 			value = "./srcs/CGI/errors/409.html";
		std::ifstream			file(value.c_str());
		if (file.is_open() == true)
		{
			while (getline(file, line))
			{
				content += line + "\n";
			}
			file.close();
		}
		else
		{
			std::cout << "ERROR\nCannot open" << std::endl;
		}
		return (content);
	}
	else
	{
		std::string 			value = "body_php";
		std::ifstream			file(value.c_str());
		if (file.is_open() == true)
		{
			while (getline(file, line))
			{
				content += line + "\n";
			}
			file.close();
		}
		else
		{
			std::cout << "ERROR\nCannot open" << std::endl;
		}
		return (content);
	}
	return (content);    
}


//////////////////////////////////////////////////////
//                                                  //
//            EXECUTION DU SCRIPT PHP-CGI           //
//                                                  //
//////////////////////////////////////////////////////

int Cgi::Exec(void)
{
	char **env = this->getMapChar();
	std::string path_cgi = "./srcs/CGI/cgi-bin/php-cgi";
	std::string path = this->getPathInfo();
	
	std::cout << BLUE << "PATH = " << this->_PathInfo << RESET << std::endl;
	int	i = 0;

	while (env[i])
	{
		std::cout << BLUE << env[i] << RESET << std::endl;
		i++;
	}

	char **tab = new char *[3];
	tab[0] = new char[path_cgi.size() + 1]; 
	std::strcpy(tab[0], path_cgi.c_str());
	tab[1] = new char[path.size() + 1]; 
	std::strcpy(tab[1], path.c_str());
	tab[2] = NULL;

	int pipefd[2];

	if (pipe(pipefd) != 0)
			return (ClearTab(tab), - 1);

	std::string path_one = "body_php";
	std::string path_two = this->getPathInfo();

	int tmp_file = ::open(path_one.c_str(), O_CREAT | O_RDWR | O_TRUNC, 00755);
	
	
	int pid = fork();
	
	if (pid < 0)
	{
		std::cout << RED << "Error\nPID" << RESET << std::endl;
			return (ClearTab(tab), - 1);
	}
	
	else if (pid == 0)
	{
		// std::cout << "Je suis l'enfant" << std::endl;        
		
		if (!(chdir(path_two.c_str())))
			return (ClearTab(tab), - 1);

		close(pipefd[1]);
				
		if (dup2(pipefd[0], 0) == -1)
			return (ClearTab(tab), - 1);

			
		if (dup2(tmp_file, 1) == -1)
			return (ClearTab(tab), - 1);

		close(pipefd[0]);
		
		if (execve(tab[0], tab, env) < 0)
			return(std::cout << "ERROR EXEC" << std::endl, -1);
	}
	else
	{
		// std::cout << "Je suis le parent" << std::endl;

		close(pipefd[0]);
		
		if (!this->getContentBody().empty() && (this->_ContentType.find("multipart/form-data")) == 0)
		{
    		int indice_debut = _ContentBody.find("filename=");
	    	std::string sous_chaine = _ContentBody.substr(indice_debut + 10); // Ajouter 10 pour sauter "filename=\"
	    	int indice_fin = sous_chaine.find("\"");
    		this->_FileName = sous_chaine.substr(0, indice_fin);
        	std::cout << "filename = " << this->_FileName << std::endl;
			
			size_t found = this->_ContentBody.find(this->_Boundary);
			this->_ContentBody.erase(0, found + this->_Boundary.size() + 2);
			found = this->_ContentBody.find("\r\n\r\n");
			this->_ContentBody.erase(0, found + 4);
			// std::cout << PURPLE << this->_ContentBody << RESET << std::endl;

			found = this->_ContentBody.find(this->_Boundary);
			for (; this->_ContentBody[found] != '\n'; found--) { ; }
			this->_ContentBody.erase(found, this->_ContentBody.size());

			std::cout << PURPLE << this->_ContentBody << RESET << std::endl;
			
			std::string tmp = "./srcs/CGI/upload/" + this->_FileName;
			std::ofstream file(tmp.c_str());
			if (!file.is_open())
        		std::cout << "Erreur lors de l'ouverture du fichier" << std::endl;

			file << this->_ContentBody;
			std::cout << "FILE :" << file << std::endl;
			file.close();

    		std::cout << "Les données ont été copiées dans le fichier" << std::endl;
		}
		if (!this->getContentBody().empty() && this->getMethod() == "POST")
		{
			int rc;
			std::string tmp = this->_ContentBody + "\r";
			rc = write(pipefd[1], this->getContentBody().data(), this->getContentBody().length());
			//rc = write(pipefd[1], tmp.c_str(), tmp.length());
			if (rc <= 0)
			{
				std::cout << RED << "ERROR\nBODY" << RESET << std::endl;
				return (ClearTab(tab), - 1);
			}
			std::cout << "WRITE VALUE " <<rc << std::endl;
		}
		close(pipefd[1]);

		int status = 0;
		if (waitpid(pid, &status, 0) == -1)
		{
			std::cout << RED << "ERROR\nWAIT" << RESET << std::endl;
			return (ClearTab(tab), - 1);
		}
		if (WIFEXITED(status) && WEXITSTATUS(status))
		{
			std::cout << RED << "ERROR\nWAIT" << RESET << std::endl;
			return (ClearTab(tab), - 1);
		}
	}
	std::cout << BOLD_GREEN << "PROCESS POST OK" << RESET << std::endl;
	ClearTab(tab);
	return (200);
}

//////////////////////////////////////////////////////
//                                                  //
//               CHECKING DES ERREURS               //
//                                                  //
//////////////////////////////////////////////////////

int Cgi::CheckTypes(void)
{
	std::string		line;
	std::string		content;
	std::ifstream	file("srcs/CGI/mimes/mimes.types");
	
	if (file.is_open() == true)
	{
		while (getline(file, line))
		{
			content += line + "\n";
    		std::istringstream iss(content);
    		std::string line2;

		    while (getline(iss, line2)) 
			{
	        	std::string value = line2.substr(0, line2.find_first_of(' '));
	        	std::string key = line2.substr(line2.find_last_of(' ') + 1);
	        	this->_mimes[key] = value; 
   			}
		}
		file.close();
	}
	else
	{
		std::cout << "ERROR\nCannot open MIMES" << std::endl;
		return (-1);
	}
	std::cout << GREEN << this->getContentType() << std::endl;
    for (std::map<std::string, std::string>::iterator it = _map_cgi_env.begin(); it != _map_cgi_env.end(); it++) 
	{
        std::string value = it->second;
        bool found = false;
        for (std::map<std::string, std::string>::iterator it2 = _mimes.begin(); it2 != _mimes.end(); it2++) 
		{
            if (it2->second == value) 
			{
                found = true;
                break;
            }
        }
        if (found)
			return (200);
    }	
	return (-1);
}


int Cgi::CheckExtension(void)
{
	std::string value = this->getPathInfo();
	std::string::size_type dotPos = value.find_last_of('.');
	if (dotPos == std::string::npos)
		return (-1);
	std::string extension = value.substr(dotPos);
	if (extension == ".html")
		return (1);
	else if (extension == ".ico")
		return (4);
	else if (extension == ".php")
		return (2);
	else if (extension == ".png" || extension == ".jpg" || extension == ".gif")
		return (3);
	return (-1);
}

//////////////////////////////////////////////////////
//                                                  //
//                 INIT ENV CGI			            //
//                                                  //
//////////////////////////////////////////////////////

int Cgi::InitEnvTab(void)
{
    std::map<std::string, std::string>::iterator it;
	this->_env_cgi = (char**)malloc(sizeof(char*) * (this->_map_cgi_env.size() + 1));
	if (!this->_env_cgi)
		return (-1);
	int i = 0;
	it = this->_map_cgi_env.begin();
	while (i < (int)this->_map_cgi_env.size())
	{
		std::string tmp = it->first + "=" + it->second + '\0';
		this->_env_cgi[i] = strdup((char*)tmp.c_str());
		if (this->_env_cgi[i] == NULL)
			return (-1);
		i++;
		++it;
	}
	this->_env_cgi[i] = NULL;
	return (0);	
}

int	Cgi::InitEnvCgi(void)
{
	if (this->getStatus() != "200 OK")
		return (-1);
	this->_map_cgi_env["REQUEST_METHOD"] = this->getMethod();
	if (this->_Method == "POST")
	{
		this->_map_cgi_env["CONTENT_LENGTH"] = this->getContentLength();
		this->_map_cgi_env["CONTENT_TYPE"] = this->getContentType(); //application/x-www-form-urlencoded // this->getContentType()
	}
	this->_map_cgi_env["SERVER_PORT"] = this->getPort();
	this->_map_cgi_env["REDIRECT_STATUS"] = "200";
	if (this->_Method == "POST")
		this->_map_cgi_env["SCRIPT_FILENAME"] = this->getPathInfo();
	this->_map_cgi_env["PATH_TRANSLATED"] = this->getPathInfo();
	this->_map_cgi_env["REQUEST_URI"] = this->getPathInfo();
	
	this->_map_cgi_env["SCRIPT_NAME"] = "./scrs/CGI/cgi-bin/php-cgi";		 	
	this->_map_cgi_env["SERVER_PROTOCOL"] = "HTTP/1.1";
	this->_map_cgi_env["SERVER_NAME"] = "localhost";
	if (this->_Method == "GET")
		this->_map_cgi_env["QUERY_STRING"] = this->getContentBody();
	else
		this->_map_cgi_env["QUERY_STRING"] = "";
	this->_map_cgi_env["GATEWAY_INTERFACE"] = "CGI/1.1";
	this->_map_cgi_env["PATH_INFO"] = this->getPathInfo();

	
	this->_map_cgi_env["HTTP_ACCEPT"] = "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8";
	this->_map_cgi_env["HTTP_ACCEPT_ENCODING"] = "gzip, deflate, br";
	this->_map_cgi_env["HTTP_ACCEPT_LANGUAGE"] = "en-US,en;q=0.5";
	// this->_map_cgi_env["HTTP_CACHE_CONTROL"] = "max-age=3600, public";
	this->_map_cgi_env["HTTP_CONNECTION"] = "keep-alive";
	// this->_map_cgi_env["HTTP_HOST"] = "localhost";
	this->_map_cgi_env["HTTP_SEC_FETCH_DEST"] = "document";			
	this->_map_cgi_env["HTTP_SEC_FETCH_MODE"] = "navigate";
	this->_map_cgi_env["HTTP_SEC_FETCH_SITE"] = "same-origin";
	this->_map_cgi_env["HTTP_SEC_FETCH_USER"] = "?1";
	// this->_map_cgi_env["HTTP_SEC_GPC"] = request_r.Get_SecGpc();
	// this->_map_cgi_env["HTTP_UPGRADE_INSECURE_REQUESTS"] =request_r.Get_UpgradeInsecureRequests();
	this->_map_cgi_env["HTTP_USER_AGENT"] = "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:102.0) Gecko/20100101 Firefox/102.0";

	if (this->InitEnvTab() == -1)
		return (-1);
	
	
	return (0);
}

//////////////////////////////////////////////////////
//                                                  //
//                 HTML TO STRING		            //
//                                                  //
//////////////////////////////////////////////////////

std::string Cgi::CompleteString(std::string html)
{
	std::string tmp;
	size_t size = 0; 
	std::ostringstream oss;
	if (this->_img == true)
	{
		// // Ouvrir l'image en binaire en mode lecture
    	std::ifstream img(this->_PathInfo.c_str(), std::ios::binary);

    	// Vérifier si le fichier est ouvert avec succès
    	// if (!img) 
        	// std::cerr << "Impossible d'ouvrir le fichier" << std::endl;

    	// Récupérer la taille de l'img en octets
    	img.seekg(0, std::ios::end);
    	long long size = img.tellg();
		// img.seekg(0, std::ios::beg);

    	// img.close();
	
    	// // Afficher la taille de l'image en octets
    	// std::cout << "Taille de l'image en octets : " << taille << std::endl;
		// std::cout << RED << size << RESET << std::endl;
    	oss << size;
		tmp = "HTTP/1.1 " + this->getStatus() + "\r\nContent-Type: image/png\r\nContent-Length: " + oss.str() + "\r\n\n";
		this->_img = false;
	}
	else if (this->CheckExtension() == 2)
	{
		size = html.size();
    	oss << size;
		tmp = "HTTP/1.1 " + this->getStatus() + "\r\nContent-Length: " + oss.str() + "\n";
	}
	else
	{
		size = html.size();
    	oss << size;
		tmp = "HTTP/1.1 " + this->getStatus() + "\r\nContent-Type: text/html\nContent-Length: " + oss.str() + "\n\n";
	}
	tmp += html;
	std::cout << BOLD_YELLOW << tmp << RESET << std::endl;
	return (tmp);
}


int Cgi::Interprate_img(void)
{
	std::string status = this->getStatus();
	std::string html = html_to_string(status);

	std::ifstream input(this->_PathInfo.c_str(), std::ios::binary);

	if (!input.is_open())
		return (-1);
	size_t ContentSize = 0;
	input.seekg(0, std::ios::end);
	ContentSize = input.tellg();

	char test[11];
	std::sprintf(test, "%lu", ContentSize);
	
	char *html_str = (char*)malloc(sizeof(char) * ContentSize + 1);
	html_str[ContentSize] = '\0';
	
	input.read(html_str, ContentSize);
	if (!(html.empty()))
	{
		html = CompleteString(html);
		this->setHtml(html);
	}
	else
		return (delete [](html_str), input.close(), -1);
	delete [](html_str);
	return (0);
}

int Cgi::Interprate_html(void)
{
	std::string status = this->getStatus();
	std::string html = html_to_string(status);
	if (!(html.empty()))
	{
		html = CompleteString(html);
		this->setHtml(html);
	}
	else
		return (-1);
	return (0);
}

int Cgi::Interprate_php_CGI(void)
{
	std::cout<<"j'execute un script php-CGI" << std::endl;
	if (this->Exec() == 404)
	{
		std::string html = html_to_string("404");
		if (!(html.empty()))
		{
			html = CompleteString(html);
			this->setHtml(html);
		}
		return (-1);
	}
	std::string html = html_to_string("1");
	if (!(html.empty()))
	{
		html = CompleteString(html);
		this->setHtml(html);
	}
	else
		return (-1);
	return(0);
}

int Cgi::init_cgi(void)
{
	//STATUS DIFFERENT DE 200 OK

	std::string html;
    if (this->InitEnvCgi() == -1)
	{
		std::cout << RED << "ERROR\ninit" << RESET <<std::endl;
		if (this->getStatus() != "200 OK")
			html = html_to_string(this->getStatus());
		else
			html = html_to_string("404");
		if (!(html.empty()))
		{
			html = CompleteString(html);
			this->setHtml(html);
			return (0);
		}
    	return (-1);
	}
	
    struct stat fileStat;

    if (stat(this->_PathInfo.c_str(), &fileStat) < 0) 
	{
		if (this->CheckExtension() == 4)
		{
			this->_Favicon = true;
			return (-1);
			// return (EXIT_FAILURE); FAVICONNNNNN
		}
		html = html_to_string("404");
		if (!(html.empty()))
		{
			html = CompleteString(html);
			this->setHtml(html);
		}
		std::cout << RED << "ERROR\nfile" << RESET <<std::endl;
        return (-1);
    }
    if (S_ISDIR(fileStat.st_mode)) 
	{
    	std::cout << "est un dossier\n";
		std::cout << GREEN << "PATH : " << this->_PathInfo << RESET << std::endl;
		std::cout << GREEN << "Autodindex : " << this->_AutoIndex << RESET << std::endl;

		
		if(this->_PathInfo[this->_PathInfo.size() - 1] == '/' && this->_AutoIndex == true)
		//AUTOINDEX
		{
			GenerateAutoIndex(this->_PathInfo);
			html = html_to_string("200 AUTO");
			std::string autoIndex = this->_PathInfo + "autoindex.html"; 
			const char* autoindex02 = autoIndex.c_str();
			remove(autoindex02);
		}
		else
		{
			this->_PathInfo = this->getIndex();
			html = html_to_string("200 OK");
		}
		if (!(html.empty()))
		{
			html = CompleteString(html);
			this->setHtml(html);
		}
		return (0);
	}
	else if (S_ISREG(fileStat.st_mode)) 
	{
        std::cout << "est un fichier\n";
    	html = html_to_string("200 OK");
		if (this->getMethod() == "DELETE")
		{
			html = html_to_string("409");
		}
		// else if (this->CheckTypes() == -1)
		// {
		// 	std::cout << RED << "ERROR\nTYPES" << RESET <<std::endl;
		// 	html = html_to_string("404");
		// }
		// if (!html.empty())
		// {
		// 	html = CompleteString(html);
		// 	this->setHtml(html);
		// 	return (-1);
		// }
		// else
		// {
			if (this->CheckExtension() == 1)
			{
				if (this->Interprate_html() == -1)
					return (-1);
			}
			else if (this->CheckExtension() == 2)
			{
				if (this->Interprate_php_CGI() == -1)
					return (-1);
			}
			else if (this->CheckExtension() == 3)
			{
      			std::cout << "EXTENSION PNG\n";
				this->_img = true;
				this->Interprate_img();
					// return (-1);
			}
			return (0);
		// }
    } 
	else 
	{
        std::cout << "n'est ni un dossier ni un fichier\n";
		html = html_to_string("404");
		if (!html.empty())
		{
			html = CompleteString(html);
			this->setHtml(html);
			return (-1);
		}
    }
	return (0);
}



void Cgi::GenerateAutoIndex(std::string path) {
    DIR* dir = opendir(path.c_str());

    if (dir == NULL) 
	{
        std::cerr << "Error: cannot open the directory\n";
        exit(EXIT_FAILURE);
    }

    std::string html_autoindex = "<html><body><ul>";

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL)
	{
        if (entry->d_name[0] != '.')
		{
            html_autoindex += "<li>";
            html_autoindex += entry->d_name;
            html_autoindex += "</li>";
        }
    }
    html_autoindex += "</ul></body></html>";

    std::ofstream file((path + "/autoindex.html").c_str());
    file << html_autoindex;
	
    file.close();

    closedir(dir);
}

void Cgi::ClearArray(void)
{
	int i = 0;
	if (this->_env_cgi)
	{
		while (this->_env_cgi[i])
		{
			free (this->_env_cgi[i]);
			i++;
		}
		free (this->_env_cgi);
	}
}

void Cgi::ClearTab(char **tab)
{
	delete []tab[0];
	delete []tab[1];
	delete []tab;
}

//////////////////////////////////////////////////////
//                                                  //
//                    GETERS                        //
//                                                  //
//////////////////////////////////////////////////////

char** Cgi::getMapChar(void) const
{
	return (this->_env_cgi);	
}

std::map<std::string, std::string> Cgi::getMap(void) const 
{
	return (this->_map_cgi_env);	
}

std::string Cgi::getIndex(void) const
{
	return (this->_Index);	
}

std::string Cgi::getHtml(void) const
{
	return (this->_Html_in_String);	
}

std::string Cgi::getAllBody(void) const
{
	return (this->_AllBody);	
}

std::string Cgi::getPathInfo(void) const
{
	return (this->_PathInfo);	
}

std::string Cgi::getStatus(void) const
{
	return (this->_Status);	
}

std::string Cgi::getMethod(void) const
{
	return (this->_Method);	
}

std::string Cgi::getContentType(void) const
{
	return (this->_ContentType);	
}

std::string Cgi::getContentBody(void) const
{
	return (this->_ContentBody);	
}

std::string Cgi::getContentLength(void) const
{
	return (this->_ContentLength);	
}

bool Cgi::getAutoIndex(void) const
{
	return (this->_AutoIndex);	
}

std::string Cgi::getPathAutoIndex(void) const
{
	return (this->_PathAutoIndex);	
}

std::string Cgi::getErrorPage(void) const
{
	return (this->_ErrorPage);	
}

std::string Cgi::getFileName(void) const
{
	return (this->_FileName);	
}

std::string Cgi::getPort(void) const
{
	return (this->_Port);	
}

std::string Cgi::getBoundary(void) const
{
	return (this->_Boundary);	
}

int Cgi::getErrorCode(void) const
{
	return (this->_ErrorCode);	
}

int Cgi::getMaxBodySize(void) const
{
	return (this->_MaxBodySize);	
}

bool Cgi::getFavicon(void) const
{
	return (this->_Favicon);	
}

//////////////////////////////////////////////////////
//                                                  //
//                    SETERS                        //
//                                                  //
//////////////////////////////////////////////////////

void Cgi::setIndex(std::string Index)
{
	this->_Index = Index;
}

void Cgi::setHtml(std::string html)
{
	this->_Html_in_String = html;
}

void Cgi::setStatus(std::string Status)
{
	this->_Status = Status;
}

void Cgi::setAllBody(std::string AllBody)
{
	this->_AllBody = AllBody;
}

void Cgi::setContentType(std::string ContentType)
{
	this->_ContentType = ContentType;
}

void Cgi::setContentBody(std::string ContentBody)
{
	this->_ContentBody = ContentBody;
}

void Cgi::setContentLength(std::string ContentLength)
{
	this->_ContentLength = ContentLength;
}

void Cgi::setPathInfo(std::string PathInfo)
{
	this->_PathInfo = PathInfo;
}

void Cgi::setMethod(std::string Method)
{
	this->_Method = Method;
}

void Cgi::setAutoIndex(bool AutoIndex) 
{
	this->_AutoIndex = AutoIndex;
}

void Cgi::setPathAutoIndex(std::string PathAutoIndex)
{
	this->_PathAutoIndex = PathAutoIndex;
}

void Cgi::setErrorPage(std::string ErrorPage)
{
	this->_ErrorPage = ErrorPage;
}

void Cgi::setFileName(std::string FileName)
{
	this->_FileName = FileName;
}

void Cgi::setPort(std::string Port)
{
	this->_Port = Port;
}

void Cgi::setBoundary(std::string Boundary)
{
	this->_Boundary = Boundary;
}

void Cgi::setErrorCode(int ErrorCode)
{
	this->_ErrorCode = ErrorCode;
}

void Cgi::setMaxBodySize(int MaxBodySize)
{
	this->_MaxBodySize = MaxBodySize;
}

void Cgi::setFavicon(bool Favicon)
{
	this->_Favicon = Favicon;
}
