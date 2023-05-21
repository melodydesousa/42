#include "webserv.hpp"

Client::Client()
{
	this->end_co = false;
	this->All_recv = false;
	this->All_send = false;
	this->Content_length = false;
	this->header_recv = false;
	this->allowed_send = false;
	this->socket = -1;
	this->len_send = 0;
	this->len_recv = 0;
	this->timer = 0;
}

Client::Client(int socket)
{
	this->end_co = false;
	this->All_recv = false;
	this->All_send = false;
	this->Content_length = false;
	this->header_recv = false;
	this->allowed_send = false;
	this->socket = socket;
	this->len_send = 0;
	this->len_recv = 0;
	this->timer = 0;
}

void Client::clear()
{
	this->header_recv = false;
	this->Content_length = false;
	this->All_recv = false;
	this->All_send = false;
	this->end_co = false;
	this->allowed_send = false;
	this->recv_str.clear();
	this->send_str.clear();
	this->request_line.clear();
	this->len_recv = 0;
	this->len_send = 0;
	this->timer = 0;
}

Client::~Client()
{
}

int	Client::ft_recv(int socket)
{
	int rc;
	memset(this->buffer_in, 0, sizeof(this->buffer_in));
	rc = recv(socket, this->buffer_in, sizeof(this->buffer_in), 0);
	// std::cout << "RC = " << rc << std::endl;
	if (rc < 0)
	{
		perror("recv() failed");
			this->end_co = true;
		return (false);
	}
	if (rc == 0)
	{
		std::cout << "Connection closed" << std::endl;
		this->end_co = true;
		return (false);
	}
	//std::cout << ".......MESSAGE DU CLIENT.......\n" << "rc = \n" << rc << buffer_in;
	this->timer = std::time(NULL);
	check_recv(rc);
	return (true);
}

void	Client::check_recv(int rc)
{
	this->request.Set_recv_str(this->recv_str.append(this->buffer_in, rc));
	//std::cout << PURPLE << "recv_str : " << this->recv_str << RESET << std::endl;
	if (this->request.find_header() == EXIT_FAILURE)
	{
		this->request.request_to_cgi();
		this->request.set_All_recv(true);
	}
	if (this->request.Get_header_recv() == true)
	{
		this->request.SetParsing(this->parsing);
		this->request.SetRequest(this->recv_str);
		this->request.Process_request();
	}	
	if (this->request.Get_All_recv() == true)
	{
		//std::cout << RED << this->request.GetHeader().c_str() << RESET << std::endl;
		//std::cout << GREEN << this->request.GetBody() << RESET << std::endl;
		this->request.request_to_cgi();
	}	
}

int Client::ft_send( int socket)
{
	int rc = 0;
	rc = send(socket, this->request.GetResponse().c_str() , this->request.get_send_body_size(), 0);
	if (rc < 0)
	{
		perror("send() failed");
		this->end_co = true;
		return (false);
	}
	if (rc == 0)
	{
		this->end_co = true;
		return (false);
	}	
	// std::cout << BOLD_BLUE << this->request.GetHeader() << std::endl;
	//std::cout << BOLD_BLUE << this->request.GetResponse().c_str() << RESET << std::endl;
	//std::cout << this->request.GetCgiStatus() << std::endl;
	check_send(rc);
	return (true);
}

void	Client::bad_request(std::string status)
{
	this->request.setCgiStatus(status);
	this->request.request_to_cgi();
}

void	Client::check_send(int rc)
{
	this->len_send += rc;
	// std::cout << RED << "len_send : " << this->len_send << "rc : " << rc << "get_send :"  << this->request.get_send_body_size() << RESET << std::endl;
	if (this->len_send >= this->request.get_send_body_size())
		this->All_send = true;
}
int	Client::fd_ready_IO( int fd)
{
	
	this->end_co = false;
	if (this->request.Get_All_recv() == false)
		ft_recv(fd);
	if (this->allowed_send == true)
	{
		ft_send(fd);
	}	
	return (0);
}

//*************************************************************//
//								GETTER						   //
//*************************************************************//

bool Client::Get_end_co( void) const
{
	return (this->end_co);
}

Request Client::Get_request()
{
	return (this->request);
}

bool Client::Get_php_to( void) const
{
	return (this->request.Get_php_to());
}

bool Client::Get_header_recv()
{
	return (this->header_recv);
}

bool Client::Get_All_recv()
{
	return (this->request.Get_All_recv());
}

bool Client::Get_All_send() const
{
	return (this->All_send);
}

bool Client::Get_favicon() const
{
	return (this->request.Get_favicon());
}
bool Client::GetWait() const
{
	return (this->request.GetWait());
}

time_t Client::Get_timer()
{
	return (this->timer);
}

long long Client::get_send_body_size(void) const
{
	return (this->request.get_send_body_size());	
}

//*************************************************************//
//								SETTER						   //
//*************************************************************//

void Client::Set_end_co(bool end_co)
{
	this->end_co = end_co;
}

void Client::Set_timer(time_t timer)
{
	this->timer = timer;
}

void Client::Set_allowed_send(bool allow)
{
	this->allowed_send = allow;
}

void Client::Set_All_send(bool send)
{
	this->All_send = send;
}

void Client::set_parsing(Parsing *parsing)
{
	this->parsing = parsing;
}
