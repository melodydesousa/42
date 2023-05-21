
#ifndef SOCKET_HPP
#define SOCKET_HPP

#define MAX_SOCKET 30000
#define MAX_SERVER 30000
#include "Client.hpp"

class Socket {
	public:
		Socket();
        ~Socket();

		void 	init_socket( void);
		void 	ft_bind( void);
		void 	ft_listen( void);
		void 	init_pfd( void );
		void 	ft_poll( void );
		int 	check_pfd( void );
		void	server( void );
		int		ft_accept( int i);
		int		ft_clean_up( void );
		int		ft_close_pfd( void );
		Parsing *get_parsing( void);
		void 	set_parsing(Parsing *parsing);
		int		Client_handler(int	i, Client * client);
		int		end_co(int	i, Client * client);
		Client *find_client(int fd);
		int		init_client(int new_fd);
		int 	check_dead_pfd(int i);
		bool	is_a_socket_master(int socket);
	

	private:
	
		struct sockaddr_in addr[MAX_SOCKET];
		struct pollfd pfd[MAX_SOCKET];
		int socket_fd[MAX_SOCKET];
		int nbr_server;
		int new_fd;
		int clean_up;
		int end_serv;
		bool purge;
		int current_size;
		int nfds;
		int timeout;
		int ret;
		int rc;
		// int len;
		// int end_co;
		std::map<int , Client *> client;
		Parsing	*parsing;
		
};

void signal_handler(int signal);

#endif
