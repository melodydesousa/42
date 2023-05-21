/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:29:48 by mede-sou          #+#    #+#             */
/*   Updated: 2023/03/24 18:20:01 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HPP
#define PARSING_HPP

#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
#include <stdexcept>
#include <cstddef>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
#include "Server.hpp"
#include <dirent.h>


class Parsing {
    public:
        Parsing();
        ~Parsing();
        Parsing & operator=(Parsing const &assign);
        Parsing(Parsing const &cpy);
        
        int init_conf_file(std::string file);
        int setVecServer();
        int createNewServer(std::vector<std::string>::iterator it);
        
        std::vector<Server *> getVectorServer();
        int getCountServer();
        std::vector<std::string> getListPort();
        
        void CleanServer();
        void makeListPort();
        void printVector();
        void set_file(std::string file);
        std::string get_file(void) const;

        class WrongArguments : public std::exception {
            public:
                virtual const char* what() const throw()
                {
                    return ("Wrong arguments\n");
                }
        };

        class ErrorFile : public std::exception {
            public:
                virtual const char* what() const throw()
                {
                    return ("Cannot open configuration file\n");
                }
        };

        class WrongFile : public std::exception {
            public:
                virtual const char* what() const throw()
                {
                    return ("Error in file\n");
                }
        };

    private:
        std::vector<std::string> vec;
        std::vector<std::string>::iterator it;
        std::vector< Server* > vec_server;
  
        std::vector<std::string> list_port;

        std::string keyword;        
        std::string file;
        std::string str;
        std::string content;
        
        int count_server;

        std::vector<std::string>::iterator tmp_it;
};

std::string check_semicolon(std::string content);
std::string first_word(std::string str, int i);
bool check_syntax(std::vector<std::string>::iterator it, std::string str);
int check_brackets(std::vector<std::string> vec);
std::string cut_whitespace(std::string str);
std::string extract_content(std::vector<std::string>::iterator it, int i, std::string keyword);
std::vector<std::string> cpp_split(std::string str, char sep);
int check_doublon_kw(std::vector<std::string> vec_kw);


#endif
