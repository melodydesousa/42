/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfontain <cfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:46:45 by amanasse          #+#    #+#             */
/*   Updated: 2023/03/24 16:08:13 by cfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
#define CGI_HPP

#include "colors.h"


class Request;


class Cgi {

	public:

		Cgi();
		~Cgi();

		int									InitEnvCgi(void);
		int									InitEnvTab(void);
		
		void								ClearArray(void);
		void								ClearTab(void);
		
		int									InterpretCgi(Request &request_r, std::map<std::string, std::string>);
		void								ClearEnvCgi(void);
		int									CheckPathInfo(void);
		int									CheckExtension(void);
		int									ClearCgi(int error, char** tab);
		std::map<std::string, std::string> 	getMap(void) const;
		char**								getMapChar(void) const;
		
		int 								Interprate_html(void);
		int 								Interprate_php_CGI(void);
		int 								Interprate_img(void);
		
		int 								CheckTypes(void);
	
		int									init_cgi(void);
		std::string							html_to_string(std::string value_error);
		std::string							CompleteString(std::string html);
		const char*							CompleteString_img(char *html, size_t ContentSize);
		std::string							Exec(void);
		std::string 						ft_getLine(std::ifstream &file);
		
		void 								GenerateAutoIndex(std::string path);

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
		std::string							getCgiPass(void) const;

		int									getErrorCode(void) const;
		int									getMaxBodySize(void) const;
		bool								getFavicon(void) const;
		bool								getPhpTo(void) const;
		long long 							get_send_body_size(void) const;


		
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
		void								setCgiPass(std::string CgiPass);


		
	private:
		char**								_env_cgi;
		char**								_tab;
		const char *						_img_to_Html;
		std::map<std::string, std::string>	_mimes;
		std::map<std::string, std::string>	_map_cgi_env;


		std::string							_line;
		std::string							_tmp1;	
		std::string							_tmp2;
		
		
		std::string							_value;	
		std::string							_completeString;
		std::string							_Html_in_String;



		std::string							_content;	

		std::string							_Port;
		std::string							_html;
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
		bool								_php_to;
		std::string							_FileName;
		std::string							_Boundary;
		std::string							_CgiPass;
		std::string							_Upload;
		long long	 						send_body_size;
};

void signal_handler(int signal);

#endif
