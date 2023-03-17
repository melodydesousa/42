/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:46:45 by amanasse          #+#    #+#             */
/*   Updated: 2023/03/16 17:32:44 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
#define CGI_HPP

#include <iostream>
#include <map>
#include "cgi.hpp"
#include "colors.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <dirent.h>
#include <bitset>

// #include <Request.hpp>

class Request;

class Cgi {

	public:

		Cgi();
		Cgi & operator=(Cgi const &cpy);
		~Cgi();

		int									InitEnvCgi(void);
		int									InitEnvTab(void);
		int									CheckTypes(void);
		void								ClearArray(void);
		int									InterpretCgi(Request &request_r, std::map<std::string, std::string>);
		void								ClearEnvCgi(void);
		int									CheckPathInfo(void);
		int									CheckExtension(void);
		int									ClearCgi(int error, char** tab);
		void								ClearTab(char** tab);
		std::map<std::string, std::string> 	getMap(void) const;
		char**								getMapChar(void) const;
		
		int 								Interprate_html(void);
		int 								Interprate_php_CGI(void);
		int 								Interprate_img(void);

		void								DeleteMethod(void);
	
		std::string							html_to_string(std::string value_error);
		std::string							CompleteString(std::string html);
		const char*							CompleteString_img(char *html, size_t ContentSize);
		int									Exec(void);
		int									init_cgi(void);

		std::string							getIndex(void) const;
		std::string							getHtml(void) const;
		const char *						getImg(void) const;
		std::string							getAllBody(void) const;
		std::string							getContentType(void) const;
		std::string							getContentLength(void) const;
		std::string							getContentBody(void) const;
		std::string							getStatus(void) const;
		std::string							getPathInfo(void) const;
		std::string							getMethod(void) const;
		bool								getAutoIndex(void) const;
		std::string							getPathAutoIndex(void) const;
		std::string							getErrorPage(void) const;
		std::string							getFileName(void) const;
		std::string							getPort(void) const;
		std::string							getBoundary(void) const;
		int									getErrorCode(void) const;
		int									getMaxBodySize(void) const;
		bool								getFavicon(void) const;
	
		void								setIndex(std::string Index);
		void								setHtml(std::string html);
		void								setImg(const char * img);
		void								setAllBody(std::string AllBody);
		void								setStatus(std::string Status);
		void								setPathInfo(std::string PathInfo);
		void								setMethod(std::string Method);
		void								setContentType(std::string ContentType);
		void								setContentLength(std::string ContentLengt);
		void								setContentBody(std::string ContentBody);
		void								setAutoIndex(bool AutoIndex);
		void								setPathAutoIndex(std::string PathAutoIndex);
		void								setErrorPage(std::string ErrorPage);
		void								setFileName(std::string FileName);
		void								setPort(std::string Port);
		void								setErrorCode(int ErrorCode);
		void								setMaxBodySize(int MaxBodySize);
		void								setFavicon(bool Favicon);
		void								setBoundary(std::string Boundary);

		void 								GenerateAutoIndex(std::string path);

		
	private:
		char**								_env_cgi;
		const char *						_img_to_Html;
		std::string							_Html_in_String;
		std::map<std::string, std::string>	_mimes;
		std::map<std::string, std::string>	_map_cgi_env;	

		std::string							_Port;
		std::string							_Index;
		std::string							_AllBody;
		std::string							_ContentType;
		std::string							_ContentLength;
		std::string							_ContentBody;
		std::string							_Status;
		std::string							_PathInfo;
		std::string							_Method;
		bool								_AutoIndex;
		std::string							_PathAutoIndex;
		std::string							_ErrorPage;
		int									_ErrorCode;
		int									_MaxBodySize;
		bool								_img;
		bool								_Favicon;
		std::string							_FileName;
		std::string							_Boundary;
		std::string							_Upload;
};


#endif
