/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfontain <cfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:24:03 by amanasse          #+#    #+#             */
/*   Updated: 2023/03/29 12:34:18 by cfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"



//////////////////////////////////////////////////////
//                                                  //
//                    Constructors                  //
//                                                  //
//////////////////////////////////////////////////////


Cgi::Cgi(void)
{
	this->_img = false;
	this->_Favicon = false;
	this->_php_to = false;
	this->_AutoIndex = false;
	this->_img_to_Html = NULL;
	this->_env_cgi = NULL;
	this->_tab = NULL;
	this->_value = "";
	this->_content = "";
	this->send_body_size = 0;
    return;
}

Cgi::~Cgi(void)
{
	this->ClearArray();
	this->ClearTab();
    return;
}

//////////////////////////////////////////////////////
//                                                  //
//                FONCTONS MEMBRES                  //
//                                                  //
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//                                                  //
//                CONVERSION HTML                   //
//                                                  //
//////////////////////////////////////////////////////

std::string Cgi::ft_getLine(std::ifstream &file)
{
	this->_tmp2 = "";

	signal(SIGINT, signal_handler);
	while (getline(file, this->_line))
	{
		this->_tmp2 += this->_line + "\n";
	}
	return (this->_tmp2);
}

std::string Cgi::html_to_string(std::string value_error)
{
	if (value_error == "200 OK" || value_error == "301")
		this->_value = this->getPathInfo();
	else if (value_error == "200 AUTO")
		this->_value = this->_PathInfo + "autoindex.html";
	else if (value_error == "400")
		this->_value = "/mnt/nfs/homes/cfontain/Documents/Cursus/webserv/srcs/CGI/errors/400.html";
	else if (value_error == "404")
	{
		this->setStatus("404");
		this->_value = getErrorPage();
	}
	else if (value_error == "405")
		this->_value = "/mnt/nfs/homes/cfontain/Documents/Cursus/webserv/srcs/CGI/errors/405.html";
	else if (value_error == "408")
		this->_value = "/mnt/nfs/homes/cfontain/Documents/Cursus/webserv/srcs/CGI/errors/408.html";
	else if (value_error == "409")
		this->_value = "/mnt/nfs/homes/cfontain/Documents/Cursus/webserv/srcs/CGI/errors/409.html";
	else if (value_error == "411")
		this->_value = "/mnt/nfs/homes/cfontain/Documents/Cursus/webserv/srcs/CGI/errors/411.html";
	else if (value_error == "413")
		this->_value = "/mnt/nfs/homes/cfontain/Documents/Cursus/webserv/srcs/CGI/errors/413.html";
	else if (value_error == "414")
		this->_value = "/mnt/nfs/homes/cfontain/Documents/Cursus/webserv/srcs/CGI/errors/414.html";
	else if (value_error == "415")
		this->_value = "/mnt/nfs/homes/cfontain/Documents/Cursus/webserv/srcs/CGI/errors/415.html";
	else if (value_error == "431")
		this->_value = "/mnt/nfs/homes/cfontain/Documents/Cursus/webserv/srcs/CGI/errors/431.html";
	else if (value_error == "500")
		this->_value = "/mnt/nfs/homes/cfontain/Documents/Cursus/webserv/srcs/CGI/errors/500.html";
	else if (value_error == "505")
		this->_value = "/mnt/nfs/homes/cfontain/Documents/Cursus/webserv/srcs/CGI/errors/505.html";
	else if (this->getMethod() == "DELETE")
	{
		if (this->getStatus() == "404")
			this->_value = getErrorPage();
		else
			this->_value = "/mnt/nfs/homes/cfontain/Documents/Cursus/webserv/srcs/CGI/html/Formulaire_delete.php";
	}
	else
		this->_value = "body_php";
		
	std::ifstream file(this->_value.c_str());
	
	if (file.is_open() == true)
		this->_content = ft_getLine(file);
	else if (value_error == "301" && file.is_open() == false)
		html_to_string("404");
	else
		this->_content = "<html><head><title>Oups</title></head><body><meta charset='utf-8'><h1>Welcome to Webserv</h1></body></html>";
	file.close();
	return (this->_content);
}


//////////////////////////////////////////////////////
//                                                  //
//            EXECUTION DU SCRIPT PHP-CGI           //
//                                                  //
//////////////////////////////////////////////////////

std::string Cgi::Exec(void)
{
	if (this->_CgiPass.empty())
		return (this->setStatus("500"), "500");
	char **env = this->getMapChar();
	
	this->_tab = new char *[3];
	this->_tab[0] = new char[this->_CgiPass.size() + 1];
	std::strcpy(this->_tab[0], this->_CgiPass.c_str());
	this->_tab[1] = new char[this->getPathInfo().size() + 1]; 
	std::strcpy(this->_tab[1], this->getPathInfo().c_str());
	this->_tab[2] = NULL;

	int pipefd[2];

	if (pipe(pipefd) != 0)
		return (this->setStatus("404"), "404");

	std::string path_one = "body_php";

	int tmp_file = ::open(path_one.c_str(), O_CREAT | O_RDWR | O_TRUNC, 00755);
	
	
	int pid = fork();
	
	if (pid < 0)
	{
		std::cout << RED << "Error\nPID" << RESET << std::endl;
			return (this->setStatus("404"), "404");
	}
	
	else if (pid == 0)
	{
		if (!(chdir(this->getPathInfo().c_str())))
			return (this->setStatus("404"), "404");
		close(pipefd[1]);
				
		if (dup2(pipefd[0], 0) == -1)
			return (this->setStatus("404"), "404");
			
		if (dup2(tmp_file, 1) == -1)
			return (this->setStatus("404"),"404");
		
		close(pipefd[0]);
		
		if (execve(this->_tab[0], this->_tab, env) < 0)
			return(std::cout << "ERROR EXEC" << std::endl, "404");
	}
	else
	{
		close(pipefd[0]);
		
		if (!this->getContentBody().empty() && (this->_ContentType.find("multipart/form-data")) == 0)
		{
    		int indice_debut = _ContentBody.find("filename=");
	    	std::string sous_chaine = _ContentBody.substr(indice_debut + 10);
	    	int indice_fin = sous_chaine.find("\"");
    		this->_FileName = sous_chaine.substr(0, indice_fin);
			
			size_t found = this->_ContentBody.find(this->_Boundary);
			this->_ContentBody.erase(0, found + this->_Boundary.size() + 2);
			found = this->_ContentBody.find("\r\n\r\n");
			this->_ContentBody.erase(0, found + 4);

			found = this->_ContentBody.find(this->_Boundary);
			for (; this->_ContentBody[found] != '\n'; found--) { ; }
			this->_ContentBody.erase(found, this->_ContentBody.size());
			
			std::string tmp = "/mnt/nfs/homes/cfontain/Documents/Cursus/webserv/srcs/CGI/upload/" + this->_FileName;
			std::ofstream file(tmp.c_str());
			if (!file.is_open())
        		std::cout << "Error\n Cannot open file" << std::endl;

			file << this->_ContentBody;

			file.close();

    		std::cout << "Transfer ok" << std::endl;
		}
	
		if (!this->getContentBody().empty() && this->getMethod() == "POST")
		{
			int rc;
			std::string tmp = this->_ContentBody + "\r";
			rc = write(pipefd[1], this->getContentBody().data(), this->getContentBody().length());
			if (rc == -1)
			{
				std::cout << RED << "Error\nwrite" << RESET << std::endl;
				this->setStatus("404");
				return ("404");
			}
		}
	
		close(pipefd[1]);

		
		int status = 0;
		if (waitpid(pid, &status, 0) == -1)
		{
			std::cout << RED << "ERROR\nWAIT" << RESET << std::endl;
			this->_php_to = true;
			this->setStatus("408");
			return ("408");
		}
		if (WIFEXITED(status) && WEXITSTATUS(status))
		{
			std::cout << GREEN << "ERROR\nWAIT" << RESET << std::endl;
			this->_php_to = true;
			this->setStatus("408");
			return ("408");
		}
	}
	return ("200");
}

//////////////////////////////////////////////////////
//                                                  //
//               CHECKING DES ERREURS               //
//                                                  //
//////////////////////////////////////////////////////

int Cgi::CheckTypes(void)
{
    std::string        line;
    std::string        content;
    std::ifstream    file("/mnt/nfs/homes/cfontain/Documents/Cursus/webserv/srcs/CGI/mimes/mimes.types");
    
	
	
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
	else if (extension == ".png" || extension == ".jpeg" || extension == ".jpg" || extension == ".gif")
		return (3);
	return (-1);
}

//////////////////////////////////////////////////////
//                                                  //
//                 INIT ENV CGI			            //
//                                                  //
//////////////////////////////////////////////////////

char* strdup_new(const char* str)
{
	if (str == NULL) 
		return NULL;
	
	size_t	len = std::strlen(str) + 1;
	char*	new_str = new char[len];
	
	std::memcpy(new_str, str, len);
	
	return (new_str);
}

int Cgi::InitEnvTab(void)
{
    std::map<std::string, std::string>::iterator it;
	
	this->_env_cgi = new char *[this->_map_cgi_env.size() + 1];
	if (!this->_env_cgi)
		return (-1);
	int i = 0;
	it = this->_map_cgi_env.begin();
	while (i < (int)this->_map_cgi_env.size())
	{
		std::string tmp = it->first + "=" + it->second + '\0';
		this->_env_cgi[i] = strdup_new((char*)tmp.c_str());
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
	
	// this->_map_cgi_env["SCRIPT_NAME"] = "/mnt/nfs/homes/cfontain/Documents/Cursus/webserv/scrs/CGI/cgi-bin/php-cgi";		 	
	this->_map_cgi_env["SCRIPT_NAME"] = this->getCgiPass();	
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
	this->_map_cgi_env["HTTP_CONNECTION"] = "keep-alive";
		
	this->_map_cgi_env["HTTP_SEC_FETCH_DEST"] = "document";			
	this->_map_cgi_env["HTTP_SEC_FETCH_MODE"] = "navigate";
	this->_map_cgi_env["HTTP_SEC_FETCH_SITE"] = "same-origin";
	this->_map_cgi_env["HTTP_SEC_FETCH_USER"] = "?1";
	this->_map_cgi_env["HTTP_USER_AGENT"] = "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:102.0) Gecko/20100101 Firefox/102.0";

	//std::cout << BOLD_RED << getAllBody() << std::endl;
	//std::cout << "PATH INFO : " << getPathInfo() << RESET << std::endl;
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
    	std::ifstream img(this->_PathInfo.c_str(), std::ios::binary);
    	img.seekg(0, std::ios::end);
    	long long size = img.tellg();
		this->send_body_size = size;
    	oss << size;
		tmp = "HTTP/1.1 " + this->getStatus() + "\r\nContent-Type: image/png\r\nContent-Length: " + oss.str() + "\r\n\n";
		this->_img = false;
	}
	else if (this->CheckExtension() == 2)
	{
		if (this->getStatus() != "200 OK")
		{
			size = html.size();
			this->send_body_size = size;
    		oss << size;
			tmp = "HTTP/1.1 " + this->getStatus() + "\r\nContent-Type: text/html\nContent-Length: " + oss.str() + "\n\n";
		}
		else
		{
			size_t Find = html.find("<!DOCTYPE html>\n");
			if (Find != std::string::npos)
				html.erase(0, Find);
			size = html.size();
			this->send_body_size = size;
			// std::cout << RED << "CONTENT BODY : " << this->_ContentBody << RESET << std::endl;
			// std::cout << RED << "TAILLE DE BODU RESPONSE : " << size << RESET << std::endl;
    		oss << size;
			tmp = "HTTP/1.1 " + this->getStatus() + "\r\nContent-Type: text/html\nContent-Length: " + oss.str() + "\n\n";
		}
	}
	else
	{
		size = html.size();
		this->send_body_size = size;
    	oss << size;
		tmp = "HTTP/1.1 " + this->getStatus() + "\r\nContent-Type: text/html\nContent-Length: " + oss.str() + "\n\n";
	}
	this->send_body_size += tmp.size();
	tmp += html;
	return (tmp);
}


int Cgi::Interprate_img(void)
{
	std::string status = this->getStatus();
	std::string html = html_to_string(status);

	std::ifstream input(this->_PathInfo.c_str(), std::ios::binary);

	if (!input.is_open())
		return (-1);
	// size_t ContentSize = 0;
	// input.seekg(0, std::ios::end);
	// ContentSize = input.tellg();
	// input.seekg(0, std::ios::beg);
	// input.close();
	if (!(html.empty()))
	{
		html = CompleteString(html);
		this->setHtml(html);
	}
	else
		return (-1);
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
	std::string	Exec_value = this->Exec();

	if (Exec_value != "200")
	{
		std::string html = html_to_string(Exec_value);
		if (!(html.empty()))
		{
			html = CompleteString(html);
			this->setHtml(html);
		}
		return (-1);
	}
	std::string html = html_to_string("PHP");
	if (!(html.empty()))
	{
		html = CompleteString(html);
		this->setHtml(html);
		remove("body_php");
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
		std::cout << GREEN << this->_AllBody << std::endl;
		// std::cout << RED << "ERROR\ninit" << RESET <<std::endl;
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

	if ((!this->_ContentType.empty()) && this->_ContentType.find("multipart/form-data") == std::string ::npos)
	{
		if (this->CheckTypes() == -1)
		{
			html = html_to_string("415");
			if (!html.empty())
			{
				html = CompleteString(html);
				this->setHtml(html);
			}			
			return (-1);
		}
	}
	if (this->getMethod() == "DELETE")
	{
		if (this->getPathInfo().find("/upload/") != std::string::npos)
		{
			if (getPathInfo().find("%20"))
			{
				size_t pos = this->_PathInfo.find("%20");
				while (pos != std::string::npos) 
				{
        			this->_PathInfo.replace(pos, 3, " "); 
        			pos = this->_PathInfo.find("%20", pos + 1);
    			}
			}
			std::remove(getPathInfo().c_str());
			std::cout << BOLD_BLUE << "DELETE FILE : " << getPathInfo() <<  RESET << std::endl;

			std::string html = html_to_string("DELETE");
			if (!(html.empty()))
			{
				html = CompleteString(html);
				this->setHtml(html);
			}
			return (0);
		}
	}

    struct stat fileStat;
    if (stat(this->_PathInfo.c_str(), &fileStat) < 0) 
	{
		if (this->CheckExtension() == 4)
		{
			this->_Favicon = true;
			return (-1);
		}
		html = html_to_string("404");
		if (!(html.empty()))
		{
			html = CompleteString(html);
			this->setHtml(html);
		}
		// std::cout << RED << "ERROR\nNot a file" << RESET <<std::endl;
        return (-1);
    }
    if (S_ISDIR(fileStat.st_mode)) 
	{
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
			this->setStatus("301");
			html = html_to_string("301");
		}
		if (!(html.empty()))
		{
			html = CompleteString(html);
			this->setHtml(html);
		}
	}
	else if (S_ISREG(fileStat.st_mode)) 
	{
        // std::cout << "est un fichier\n";
    	html = html_to_string("200 OK");
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
			this->_img = true;
			if (this->Interprate_img() == -1)
				return (-1);
		}
		else
		{
			html = html_to_string("415");
			if (!html.empty())
			{
				html = CompleteString(html);
				this->setHtml(html);
				return (-1);
			}
		}
    } 
	else 
	{
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
            html_autoindex += "<a href='" + std::string(entry->d_name) + "'>";
            html_autoindex += entry->d_name;
            html_autoindex += "</a></li>";
        }
    }
    html_autoindex += "</ul></body></html>";

    std::ofstream file((path + "/autoindex.html").c_str());
    file << html_autoindex;
	
    file.close();

    closedir(dir);
}


void Cgi::ClearTab(void)
{
	if (this->_tab)
	{
		delete []this->_tab[0];
		delete []this->_tab[1];
		delete []this->_tab;
	}
}

void Cgi::ClearArray(void)
{
    int i = 0;
    if (this->_env_cgi)
    {
        while (this->_env_cgi[i])
        {
            delete[] this->_env_cgi[i];
            i++;
        }
        delete[] this->_env_cgi;
        this->_env_cgi = 0;
    }
}

void signal_handler2(int signal)
{
	if (signal == SIGINT)
		exit(signal);
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

std::string Cgi::getCgiPass(void) const
{
	return (this->_CgiPass);
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

bool Cgi::getPhpTo(void) const
{
	return (this->_php_to);	
}

long long Cgi::get_send_body_size(void) const
{
	return (this->send_body_size);	
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

void Cgi::setCgiPass(std::string CgiPass)
{
	this->_CgiPass = CgiPass;
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
