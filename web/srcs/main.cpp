#include "Parsing.hpp"
#include "webserv.hpp"
#include "Request.hpp"
#include "cgi.hpp"
#include "colors.h"

Parsing parsing;
Socket soso;

void signal_handler(int signal)
{
	if (signal == SIGINT)
		exit(signal);
}	

int main(int ac, char **av)
{
	(void) av;

    // if (ac < 2)
    //   return (std::cerr << "Wrong number of arguments\n", 1);
	signal(SIGINT, signal_handler);
	parsing.set_file(av[1]);

    parsing.init_conf_file(parsing.get_file());
	
	int port;
	port = 0;
	//if (ac == 2)
	port = 8080;
	if (ac == 3)
	{
		(void)soso;
		soso.set_parsing(&parsing);
		soso.server();
	}	
	return 0;
}
