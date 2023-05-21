
#include "Request.hpp"

Request::Request() : b_method(false), bad_request(false), header_recv(false), Content_length(false), All_recv(false) , wait(false), loc(NULL)
{
	this->ContentLength = 0;
}

Request::~Request()
{
	this->request_split_line.clear();
	this->request_split_space.clear();
	this->location_split.clear();
	this->req_location.clear();
}


//*************************************************************//
//								SETTER						   //
//*************************************************************//

void Request::SetMethod(std::string &str)
{
	this->Method = str;
}

void Request::set_All_recv(bool all_recv) 
{
	this->All_recv = all_recv;
}

void Request::set_wait(bool wait) 
{
	this->wait = wait;
}

void Request::SetPort(std::string &str)
{
	this->Port = str;
}

void Request::SetHost(std::string &str)
{
	this->Host = str;
}

void Request::SetR_Location(std::string &str)
{
	this->R_Location = str;
}

void Request::SetProtocol(std::string &str)
{
	this->Protocol = str;
}

void Request::SetReq_location(std::vector<std::string> &loc)
{
	this->req_location = loc;
}

void Request::SetParsing(Parsing *parsing)
{
	this->parsing = parsing;
}

void Request::SetServer(Server *serv)
{
	this->serv = serv;
}

void Request::SetRequest(std::string request)
{
	this->request = request;
}

void Request::SetResponse(std::string Response)
{
	this->Response = Response;
}

void Request::SetBody(std::string Body)
{
	this->Body = Body;
}

void Request::SetHeader(std::string Header)
{
	this->Header = Header;
}

void Request::Set_recv_str(std::string str)
{
	this->recv_str = str;
}

void Request::setBoundary(std::string str)
{
	this->Boundary = str;
}

void Request::SetContentLength(unsigned long int ContentLength)
{
	this->ContentLength = ContentLength;
}

void Request::setCgiStatus( std::string status)
{
	this->cgi.setStatus(status);
}

//*************************************************************//
//								GETTER						   //
//*************************************************************//

std::string Request::GetMethod( void) const
{
	return (this->Method);
}

std::string Request::GetPort( void) const
{
	return (this->Port);
}

std::string Request::GetHost( void) const
{
	return (this->Host);
}

std::string Request::GetR_Location( void) const
{
	return (this->R_Location);
}

std::string Request::GetProtocol( void) const
{
	return (this->Protocol);
}

Parsing *Request::GetParsing( void) const
{
	return (this->parsing);
}

Server *Request::GetServer( void) const
{
	return (this->serv);
}

bool Request::Get_php_to( void) const
{
	return (this->cgi.getPhpTo());
}

bool Request::GetBmethod( void) const
{
	return (this->b_method);
}

bool Request::GetWait( void) const
{
	return (this->wait);
}

bool Request::Get_All_recv( void) const
{
	return (this->All_recv);
}

bool Request::Get_header_recv( void) const
{
	return (this->header_recv);
}

std::string Request::GetResponse( void) const
{
	return (this->Response);
}

std::string Request::GetBody( void) const
{
	return (this->Body);
}

std::string Request::GetHeader( void) const
{
	return (this->Header);
}

std::string Request::Get_recv_str( void) const
{
	return (this->recv_str);
}

std::string Request::GetBoundary( void) const
{
	return (this->Boundary);
}

unsigned long int Request::GetContentLength( void) const
{
	return (this->ContentLength);
}

bool Request::Get_favicon( void) const
{
	return (this->cgi.getFavicon());
}

long long Request::get_send_body_size(void) const
{
	return (this->cgi.get_send_body_size());	
}

void Request::request_to_cgi( void )
{
	if (this->cgi.getStatus().empty())
	{	
		this->cgi.setStatus("200 OK");
		if (check_Method() == EXIT_FAILURE)
		{
			this->cgi.setStatus("405");
			this->cgi.init_cgi();
			this->SetResponse(this->cgi.getHtml());
			return ;
		}
		this->cgi.setMethod(this->GetMethod());
		if (this->GetContentLength())
		{
			std::ostringstream oss;
			oss << this->GetContentLength();
			std::string length = oss.str();
			this->cgi.setContentLength(length);
		}
		this->cgi.setAllBody(this->Header + this->Body);

		if (this->cgi.getMethod() == "GET")
		{
			size_t find = this->R_Location.find("?");
			if (find != std::string::npos)
			{
				this->cgi.setPathInfo(this->loc->getRoot() + this->R_Location.substr(0, find));
				this->cgi.setContentBody(this->R_Location.substr(find + 1, this->R_Location.size()));
			}
			else
				this->cgi.setPathInfo(this->loc->getRoot() + this->R_Location);
		}
		else if (this->cgi.getMethod() == "POST"  || this->cgi.getMethod() == "DELETE")
		{
			this->cgi.setContentBody(this->Body);
			this->cgi.setPathInfo(this->loc->getRoot() + this->R_Location);
			if (this->Boundary.length() > 0)
				this->cgi.setBoundary(this->Boundary);
		}
		this->cgi.setErrorCode(this->loc->getErrorCode());
		this->cgi.setErrorPage(this->loc->getErrorPage());
		this->cgi.setMaxBodySize(this->loc->getBodySize());
		if (this->loc->getIndex().size() == 0)
			this->loc->setIndex(this->serv->getIndex());
		this->cgi.setIndex(this->loc->getIndex());
		this->cgi.setAutoIndex(this->loc->getAutoIndex());
		this->cgi.setPathAutoIndex(this->loc->getPathAutoIndex());
		this->cgi.setPort(this->GetPort());
		this->cgi.setCgiPass(this->loc->getCgiPass());
	}
	this->cgi.init_cgi();
	this->SetResponse(this->cgi.getHtml());
}

int Request::parse_body_length()
{

	if (this->ContentLength == 0 && this->GetBody().size() != 0)
	{
		this->cgi.setStatus("411");
		// std::cout << "ERROR Content Length not accurate\n";
		return (EXIT_FAILURE);
	}
	else if (this->ContentLength < this->GetBody().size())
	{
		this->cgi.setStatus("411");
		// std::cout << "ERROR Content Length not accurate\n";
		return (EXIT_FAILURE);
	}
	else if (this->ContentLength == this->GetBody().size())
	{
		if (this->cgi.getContentType() == "multipart/form-data;")
		{
			size_t found = this->Body.find(this->Boundary);
			this->Body.erase(0, found + this->Boundary.size() + 2);
			found = this->Body.find(this->Boundary);
			for (; this->Body[found] != '\n'; found--) { ; }
			this->Body.erase(found, this->Body.size());
		}
		this->All_recv = true;
	}
	return (EXIT_SUCCESS);
}


int Request::parse_content_length(std::string str)
{
	size_t i = 0;
	size_t j = 0;

	while (i < str.length() && isspace(str[i]))
		i++;
	if (i == str.length())
	{
		this->cgi.setStatus("411");
		// std::cout << "Content Length \n";
		return (EXIT_FAILURE);
	}	
	while (i < str.length() && isdigit(str[i]))
		i++;
	j = i;
	while (j < str.length() && isspace(str[j]))
		j++;
	if (j > 9)
	{
		this->cgi.setStatus("413"); // quel statut ?
		// std::cout << "Content Length ERROR\n TOO BIG\n";
		return (EXIT_FAILURE);
	}
	i = j;
	if (i != str.length() || str.length() == 0)
	{
		this->cgi.setStatus("400");
		std::cout << "Content Length ERROR\n";
		return (EXIT_FAILURE);
	}	
	else
	{
		this->ContentLength = atoi (str.c_str());
		this->SetContentLength(this->ContentLength);
	}
	return (EXIT_SUCCESS);
}

int Request::check_Protocol()
{
	if (this->GetProtocol() != "HTTP/1.1")
	{
		this->cgi.setStatus("505");
		// std::cout << "ECHEC PROTOCOL" << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int Request::check_Method()
{
	size_t pos;
	if (this->loc == NULL)
		pos = this->serv->getMethods().find(this->GetMethod());
	else
		pos = this->loc->getMethods().find(this->GetMethod());
	if (pos == std::string::npos)
	{
		this->cgi.setStatus("405");
		// std::cout << "ECHEC METHOD" << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void Request::find_location()
{
	size_t pos;
	this->loc_found = false;
	size_t len = this->location_split.size() - 1;

	std::vector<Location *>::iterator it;
	std::vector< Location* > loc = serv->getVectorLocation();

	for (size_t i = 0; i < this->location_split.size(); i++)
	{
		pos = this->location_split[len].find(".");
		size_t pos2 = this->location_split[len].find_first_of("?");
		if (pos != std::string::npos)
		{
			if (pos2 == std::string::npos)
				pos2 = this->location_split[len].size();
			std::string extension = this->location_split[len].substr(pos, pos2 - pos);
			for (it = loc.begin(); it != loc.end(); ++it)		
			{
				pos = (*it)->getName().find(extension);
				if (pos != std::string::npos)
				{
					this->loc_found = true;
					this->loc = (*it);
					return;
				}
			}
		}
		len--;
	}
	len = this->location_split.size() - 1;
	for (size_t i = 0; i < this->location_split.size(); i++)
	{
		for (it = loc.begin(); it != loc.end(); ++it)		
		{
			pos = (*it)->getName().find(this->location_split[len]);
			if (pos != std::string::npos)
			{
				this->loc_found = true;
				this->loc = (*it);
				return;
			}
		}
		len--;
	}
	for (it = loc.begin(); it != loc.end(); ++it)		
	{
		if ((*it)->getName() == "/")
		{
			this->loc_found = true;
			this->loc = (*it);
			return;
		}
	}
	if (it == loc.end())
	{
		this->loc_found = true;
		this->serv->makeDefaultLocation();
		find_location();	
	}
}

Server *Request::find_port( void )
{
	std::vector<Server *> serv = this->parsing->getVectorServer();
	std::vector<Server *>::iterator it;
	int i = 0;
	for (it = serv.begin(); it != serv.end(); ++it)
	{
		if ((*it)->getPort() == this->Port)
		{
			this->index_server = i;
			break;
		}	
		i++;
	}
	if (i == (int)serv.size())
		return (NULL);
	return ((*it));
}

int Request::check_lenght_body(std::string length)
{
	if (this->GetMethod() != "POST")
	{
		this->cgi.setStatus("400");
		return (EXIT_FAILURE);
	}	
	Content_length = true;
	if (parse_content_length(length) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parse_body_length() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int Request::check_request()
{
	if (this->Method.empty() || this->R_Location.empty() || this->Protocol.empty() 
		|| this->Host.empty() || this->Port.empty())
	{
		this->bad_request = true;
		this->cgi.setStatus("400");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int Request::find_content_info(std::string findContentLine)
{
	std::vector<std::string> tmp = cpsplit(findContentLine, " ");

	size_t found = findContentLine.find("Content-Type:");
	if (found != std::string::npos)
	{
		if (tmp.size() > 1)
			this->cgi.setContentType(tmp[1]);
		if (this->cgi.getContentType() == "multipart/form-data;" && tmp.size() > 2)
		{
			this->cgi.setContentType(tmp[1] + " " + tmp[2]);
			setBoundary(tmp[2].substr(9, tmp[2].size() - 9));
		}
		return (EXIT_SUCCESS);
	}	
	size_t found2 = findContentLine.find("Content-Length:");
	if (found2 != std::string::npos)
	{
		if (tmp.size() > 1 && this->check_lenght_body(tmp[1]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}

int Request::find_host(std::string findHostLine)
{
	std::vector<std::string> tmp;
	size_t found = findHostLine.find("Host:");

	if (found != std::string::npos)
	{
		tmp = cpsplit(this->request_split_space[1], ":");
		if (tmp.size() > 1)
		{
			this->SetHost(tmp[0]);
			this->SetPort(tmp[1]);
			this->serv = this->find_port();
			if (this->serv == NULL)
				return (EXIT_FAILURE);
			if (tmp[0] == "localhost" || this->serv->getHost() == tmp[0])
				return (EXIT_SUCCESS);
			size_t i;
			for (i = 0; i < this->serv->getName().size(); i++)
			{
				if (this->serv->getName()[i] == tmp[0])
					return (EXIT_SUCCESS);
			}
			if (i == this->serv->getName().size())
			{
				this->cgi.setStatus("400");
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}

int Request::find_header() 
{
	size_t found = 0;
	found = this->recv_str.find("\r\n\r\n", 0);
	size_t found2 = this->recv_str.find("\r\n", 0);
	if (found2 != std::string::npos)
	{
		if (check_startLine(this->recv_str.substr(0, found2)) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (found == std::string::npos)
	{
		// std::cout << "Not all header yet" << std::endl;
	}
	else
	{
		this->SetHeader(this->recv_str.substr(0, found));
		this->SetBody(this->recv_str.substr(found + 4, this->recv_str.size() - found + 4));
		this->header_recv = true;
	}
	return (EXIT_SUCCESS);
}

int Request::check_startLine(std::string startLine)
{
	std::vector<std::string> split_startline = cpsplit(startLine, " ");

	if (split_startline.size() > 1 && split_startline[1].size() > 1000)
	{
		this->cgi.setStatus("414");
		// std::cerr << "Error: Request-URI Too Long\n";
		return (EXIT_FAILURE);
	}
	if (split_startline.size() != 3)
	{
		this->cgi.setStatus("400");
		// std::cerr << "Error: Bad Request\n";
		return (EXIT_FAILURE);
	}
	this->SetMethod(split_startline[0]);
	this->SetR_Location(split_startline[1]);
	this->SetProtocol(split_startline[2]);
	if (check_Protocol() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	
	if (this->GetMethod() != "POST" && this->GetMethod() != "GET" && this->GetMethod() != "DELETE")
	{
		this->cgi.setStatus("405");
		// std::cerr << "Error: Method Not Allowed\n";
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int Request::check_doublon_keywords(std::vector<std::string> vec_kw)
{
	std::vector<std::string>::iterator it = vec_kw.begin();
	for (it = vec_kw.begin(); it != vec_kw.end(); ++it)
	{
		if (std::count(vec_kw.begin(), vec_kw.end(), *it) > 1 && this->GetMethod() != "POST")
		{
			this->cgi.setStatus("400");
			// std::cerr << "Error: Bad Request\n";
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int Request::parsing_header(void)
{
	std::vector<std::string> tmp;
	std::vector<std::string> vector_kw;

	this->request_split_line = cpsplit(this->Header, "\r\n"); 
	for (size_t j = 1; j < this->request_split_line.size(); j++)
	{
		if (this->request_split_line[j].size() > 10000)
		{
			this->cgi.setStatus("431");
			// std::cerr << "Error: Request header field too large\n";
			return (EXIT_FAILURE);
		}
		this->request_split_space = cpsplit(this->request_split_line[j], " ");
		int len = this->request_split_space[0].length() - 2;
		if (isspace(this->request_split_space[0][len]) != 0)
		{
			this->cgi.setStatus("400");
			// std::cerr << "Error: Bad Request\n";
			return (EXIT_FAILURE);
		}

		vector_kw.push_back(this->request_split_space[0]);
		if (find_host(this->request_split_line[j]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (find_content_info(this->request_split_line[j]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		this->request_split_space.clear();
	}
	if (this->Content_length == false)
	{
		if (this->GetBody().size() == 0)
			this->All_recv = true;
		if (this->GetBody().size() != 0)
		{
			this->cgi.setStatus("411");
			// std::cout << "ERROR Body with no length information\n";
			return (EXIT_FAILURE);
		}
	}		
	this->request_split_line.clear();
	if (check_doublon_keywords(vector_kw) == EXIT_FAILURE)
		return(EXIT_FAILURE);
	return(EXIT_SUCCESS);	
}

int Request::parsing_request( void )
{
	if (parsing_header() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	this->location_split = cpsplit(this->GetR_Location(), "/");
	return(EXIT_SUCCESS);
}

int Request::Process_request()
{
	// print_request();
	if (this->parsing_request() == EXIT_FAILURE)
	{
		if (this->cgi.getStatus().empty())
			this->cgi.setStatus("400");
		this->All_recv = true;
		return (EXIT_FAILURE);
	}
	if (this->check_request() == EXIT_FAILURE)
	{
		if (this->cgi.getStatus().empty())
			this->cgi.setStatus("400");
		this->All_recv = true;
		return (EXIT_FAILURE);
	}	
	this->find_location();
	
	if (this->ContentLength > (unsigned long)this->loc->getBodySize())
	{
		this->cgi.setStatus("413");
		this->All_recv = true;
		return (EXIT_FAILURE);
	}
	else if (this->Content_length == false && this->Method == "POST")
	{
		this->cgi.setStatus("411");
		this->All_recv = true;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void Request::print_request( void )
{
	std::cout << RED << "REQUEST = " << this->request << RESET << std::endl;
	// std::cout << "METHOD = " << this->Method << std::endl;
	// std::cout << "REQUEST LOCATION = " << this->R_Location << std::endl;
	// std::cout << "PROTOCOL = " << this->Protocol << std::endl;
	// std::cout << "HOST = " << this->Host << std::endl;
	// std::cout << "PORT = " << this->GetPort() << std::endl;
}
