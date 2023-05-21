/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:01:54 by cfontain          #+#    #+#             */
/*   Updated: 2023/03/27 13:30:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <cstdio>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <poll.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <map>
#include <vector>
#include <fstream>
#include <istream>
#include <string>
#include <stdlib.h>
#include "Request.hpp"
#include "Parsing.hpp"
#include "Socket.hpp"
#include "cgi.hpp"
#include "Client.hpp"
#include <csignal>
#include <ctime>

#include <iostream>
#include <fstream>
#include <sys/wait.h>
#include <cstdlib>
#include <dirent.h>
#include <bitset>

#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0


std::vector<std::string> cpsplit(std::string test, char sep);
void	print_vector(std::vector<std::string> vec);
void	print_vector_m(std::vector<std::map<std::string, std::string> > vec_m);	
int	server(int port, Parsing *parsing);

#endif
