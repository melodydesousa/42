#include "webserv.hpp"

Socket::Socket()
{
	this->clean_up = false;
	this->end_serv = false;
	this->purge = false;
	this->nbr_server = 0;
	this->new_fd = -1;
	this->nfds = 0;
	this->timeout = (3 * 1000);
}

Socket::~Socket()
{
	std::map<int , Client *>::iterator it;
	for (it = this->client.begin(); it != this->client.end(); ++it)
	{
		if (it->second)
			delete it->second;
	}
	ft_close_pfd();
}



/****************************** INIT_SOCKET **********************************
socket : Créer un point de communication et renvoie un descripteur
setsockopt : Permet de rendre le socket non bloquant
fcntl : Permet la réutilisation des sockets liés à ce port, evite le TIME_WAIT
******************************************************************************/

void Socket::init_socket( void)
{
	this->nbr_server = this->parsing->getListPort().size();
	for (int i = 0; i < this->nbr_server; i++)
	{
		int on = 1;	
		this->socket_fd[i] = socket(AF_INET, SOCK_STREAM, 0);
		if (this->socket_fd[i] == -1)
		{
			perror("socket() failed");
			exit (EXIT_FAILURE);
		}
		this->rc = setsockopt(this->socket_fd[i], SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
		 if (this->rc < 0)
		{
			perror("setsockopt() failed");
			close(this->socket_fd[i]);
			exit (EXIT_FAILURE);
		}
		this->rc = fcntl(this->socket_fd[i], F_SETFL, O_NONBLOCK);
		if (this->rc < 0)
		{
			perror("fcntl() failed");
			close(this->socket_fd[i]);
			exit (EXIT_FAILURE);
		}
	}
}

/********************************** FT_BIND ***********************************
Personne ne sait l'intérêt de sin_zero, les gens mettent la variable à zero 
alors on va faire pareil.
******************************************************************************/

void    Socket::ft_bind( void )
{
	int port;

	for (int i = 0; i < nbr_server; i++)
	{
		std::cout << GREEN <<"PORT : "<< this->parsing->getListPort()[i] << RESET << std::endl;
		this->addr[i].sin_family = AF_INET;
		this->addr[i].sin_addr.s_addr = INADDR_ANY; /* use my IP adresse */
		port = atoi(this->parsing->getListPort()[i].c_str());
		this->addr[i].sin_port = htons(port);
		memset(this->addr[i].sin_zero, 0, sizeof(this->addr[i].sin_zero));
		if (bind(socket_fd[i], (struct sockaddr*)&addr[i], sizeof(sockaddr))	< 0)
		{
			perror("bind() failed");
			close(socket_fd[i]);
			exit(EXIT_FAILURE);
		}
	}    
}

/********************************** FT_LISTEN**********************************
 * 
******************************************************************************/

void    Socket::ft_listen( void )
{
	for (int i = 0; i < nbr_server; i++)
	{
		if (listen(socket_fd[i], 1000) < 0)
		{
			perror("listen() failed");
			close(socket_fd[i]);
			exit(EXIT_FAILURE);
		}
	}        
}

/********************************** INIT_PFD***********************************
******************************************************************************/

void Socket::init_pfd( void )
{
	memset(pfd, 0, sizeof(pfd));
	for (int i = 0; i < nbr_server; i++)
	{
		this->pfd[i].fd = this->socket_fd[i];
		this->pfd[i].events = POLLIN;
	}
	  
}

/********************************** FT_POLL ***********************************
Poll prend en paramètre un tableau de structure de fd. C'est lui qui contrôle
quel socket est prêt à envoyer ou recevoir des données. Il renvoit le nombre
de fd prêt à effectuer une opération I/O.
******************************************************************************/

void Socket::ft_poll( void )
{
	nfds = nbr_server;
	do
	{
		ret = poll(pfd, nfds, timeout);
		for (int i = 0; i < nfds; i++)
		{
			//std::cout << "FD : "<< pfd[i].fd <<"EVENTS " << pfd[i].events << "REVENTS "<< pfd[i].revents<< std::endl;
		}
		signal(SIGINT, signal_handler);
		if (ret < 0)
		{
			perror("poll() failed");
			break;
		}
		current_size = nfds;
		if (ret == 0)
		{
			for (int i = 0; i < current_size; i++)
			{
				if (this->is_a_socket_master(pfd[i].fd) == 0)
				{
					if (check_dead_pfd(i) == EXIT_FAILURE)
						purge = true;
				}		
			}
			if (purge == false)
				continue;
		}
		check_pfd();
		if (clean_up == TRUE)
			ft_clean_up();
	} while (end_serv == FALSE);
}

int Socket::check_pfd( void )
{
	for (int i = 0; i < current_size; i++)
	{
			if (pfd[i].revents == 0)
			{
				if (this->is_a_socket_master(pfd[i].fd) == 0)
				{
					
					if (check_dead_pfd(i) == EXIT_SUCCESS)
						continue;
				}		
			}
			else if (pfd[i].revents != POLLIN && pfd[i].revents != 4 && pfd[i].revents != 5)
			{
				if (this->is_a_socket_master(pfd[i].fd) == 0)
				{
					Client *client = this->find_client(pfd[i].fd);
					client->Set_end_co(true);
					end_co(i, client);
					break;
				}	
			}
			if (this->is_a_socket_master(pfd[i].fd) == 1)
			{
				do
				{
					if (ft_accept(i) == FALSE)
						break;
				} while (this->new_fd != -1);
			}
			else
			{
				Client *client = this->find_client(pfd[i].fd);
				Client_handler(i, client);
				if (client->Get_end_co() == true)
					end_co(i, client);
			}
	}
	return (0);
}

int		Socket::Client_handler(int	i, Client * client)
{
	if	(client->Get_end_co() == false)
	{
		client->set_parsing(this->get_parsing());
		if (pfd[i].revents == 4 || pfd[i].revents == 5)
			client->Set_allowed_send(true);
		client->fd_ready_IO(pfd[i].fd);
		if (client->Get_All_recv() == true &&  client->Get_All_send() == false && client->Get_favicon() == false)
			pfd[i].events |= POLLOUT;
		else if (client->Get_favicon() == true)
			client->Set_All_send(true);
		if (client->Get_All_send() == true)
		{
			client->Set_end_co(true);
			pfd[i].events = POLLIN;
		}
	}
	return (0);
}

int		Socket::end_co(int i, Client *client)
{
	delete client;
	this->client.erase(pfd[i].fd);
	close(pfd[i].fd);
	pfd[i].fd = -1;
	this->clean_up = true;
	return (0);
}

bool	Socket::is_a_socket_master(int socket)
{
	for (int i = 0; i < nbr_server; i++)
	{
		if (socket == socket_fd[i])
			return (TRUE);
	}	
	return (FALSE);
}

int	Socket::ft_accept( int i)
{
	if (this->nfds < 100)
	{
		new_fd = accept(socket_fd[i], NULL, NULL);
		if (new_fd < 0)
		{
			if (errno != EWOULDBLOCK)
			{
				perror("accept() failed");
				end_serv = TRUE;
			}
			return (FALSE);
		}
		init_client(new_fd);
	}
	else
		return (FALSE);
	return (TRUE);
}

int	Socket::init_client(int new_fd)
{
	this->client.insert(std::pair<int , Client *> (new_fd, new Client(new_fd)));
	Client *client = this->find_client(new_fd);
	client->Set_timer(std::time(NULL));
	
	pfd[nfds].fd = new_fd;
	pfd[nfds].events = POLLIN;
	pfd[nfds].revents = 0;
	nfds++;
	return (0);
}

Client *Socket::find_client(int fd)
{
	std::map<int , Client *>::iterator it;
	it = this->client.find(fd);
	return (it->second);
}

void Socket::set_parsing(Parsing *parsing)
{
	this->parsing = parsing;
}

Parsing *Socket::get_parsing( void)
{
	return (this->parsing);
}

int Socket::ft_clean_up( void )
{
	clean_up = FALSE;
	for(int i = 0; i < nfds; i++)
	{
		if (pfd[i].fd == -1)
		{
			for(int j = i; j < nfds; j++)
			{
				pfd[j].fd = pfd[j+1].fd;
				pfd[j].events = pfd[j+1].events;
				pfd[j].revents = pfd[j+1].revents;
			}
			i--;
			nfds--;
		}
	}
	return (0);
}

int	Socket::ft_close_pfd( void )
{
	for (int i = 0; i < nfds; i++)
	{
		if (pfd[i].fd >= 0)
			close(pfd[i].fd);
	}
	return (0);
}

void Socket::server( void )
{
	this->init_socket();
	this->ft_bind();
	this->ft_listen();
	this->init_pfd();
	this->ft_poll();
}

int Socket::check_dead_pfd(int i)
{
	time_t actual_time;
	time_t res;

	Client *client = this->find_client(pfd[i].fd);
	if (client->Get_end_co() == true)
		return (EXIT_FAILURE);

	actual_time = std::time(NULL);
	res = client->Get_timer();
	if (res != 0)
	{
		if ((actual_time - res)  > 15)
		{
			std::cout << "TIME_OUT\n";
			if (client->Get_php_to() == true)
			{
				client->bad_request("404");
				this->pfd[i].events |= POLLOUT;
			}
			else
				client->Set_end_co(true);
			return (EXIT_FAILURE);
		}	
	}
	return (EXIT_SUCCESS);
}
