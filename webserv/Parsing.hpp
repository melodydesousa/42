/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:19:55 by mede-sou          #+#    #+#             */
/*   Updated: 2023/02/20 14:47:37 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HPP
#define PARSING_HPP

#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <stdexcept>
#include <cstddef>
#include <algorithm>
#include <vector>

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


#endif
