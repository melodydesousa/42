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
	signal(SIGINT, signal_handler);
	if (ac > 2)
	{
		std::cerr << "Error\nToo many arguments" << std::endl;
		return 1;
	}
	if (ac == 2)
		parsing.set_file(av[1]);
    if (parsing.init_conf_file(parsing.get_file()) == EXIT_FAILURE)
		return 1;
	soso.set_parsing(&parsing);
	soso.server();
	return 0;
}
