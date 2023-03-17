#include "Client.hpp"

Client::Client()
{
	this->end_co = false;
	this->All_recv = false;
	this->All_send = false;
	this->Content_length = false;
	this->header_recv = false;
	this->allowed_send = false;
	this->socket = -1;
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
	std::cout << "CLIENT DESTRUCTOR\n";
}




/*
	regle a implementer :
	- intégrer la partie parsing de la length dans request pour setup les codes d'erreurs
	- faire une surchage egale de request pour remettre a zero
*/


int	Client::ft_recv( int i )
{
	int rc;
	(void)i;
	memset(this->buffer_in, 0, sizeof(this->buffer_in));
	//std::cout << YELLOW "rec with i : " << i << "pfd = " << socket << std::endl;
	rc = recv(socket, buffer_in, sizeof(buffer_in), 0);
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
	// std::cout << ".......MESSAGE DU CLIENT.......\n" << buffer_in;
	this->timer = std::time(NULL);
	this->request.Set_recv_str(this->recv_str.append(buffer_in, rc));

	if (this->request.find_header() == EXIT_FAILURE)
	{
		this->request.request_to_cgi();
		this->All_recv = true;
	}
	if (this->request.Get_header_recv() == true)
	{
		this->request.SetParsing(this->parsing);
		this->request.SetRequest(this->recv_str);
		if (this->request.Process_request() == EXIT_FAILURE)
			this->request.request_to_cgi();
	}	
	if (this->request.Get_All_recv() == true)
	{
		std::cout << RED << this->request.GetHeader().c_str() << RESET << std::endl;
		std::cout << GREEN << this->request.GetBody() << RESET << std::endl;
		this->request.request_to_cgi();
	}	
	return (true);
}

int Client::ft_send( int i )
{
	int rc;
	(void)i;
	memset(this->buffer_out, 0, sizeof(this->buffer_out));
	rc = send(socket, this->request.GetResponse().data(), strlen(this->request.GetResponse().c_str()), 0);
	if (rc < 0)
	{
		perror("send() failed");
		this->end_co = true;
		return (false);
	}
	//// IMPORTANT IL FAUT CHECKER AUSSI 0 SINON C'EST ZERO !!!!!!!!!!!!!!!
	this->len_send += rc;
	this->All_send = true;
	return (false);
}

int	Client::fd_ready_IO( int i)
{
	this->end_co = false;
	if (this->request.Get_All_recv() == false)
		ft_recv(i);
	if (this->allowed_send == true)
	{
		ft_send(i);
	}	
	return (0);
}

bool Client::Get_end_co( void) const
{
	return (this->end_co);
}

void Client::set_parsing(Parsing *parsing)
{
	this->parsing = parsing;
}

Request Client::Get_request()
{
	return (this->request);
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

time_t Client::Get_timer()
{
	return (this->timer);
}

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
