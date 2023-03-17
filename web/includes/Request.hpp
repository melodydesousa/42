#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Parsing.hpp"
#include "Server.hpp"
#include "Location.hpp"
#include "cgi.hpp"

class Request {

	public:
		Request();
		~Request();
		Server *find_port( void );
		void request_to_cgi( void );
		bool GetBmethod( void) const;
		void find_location();
		int check_Method();
		int check_Protocol();
		int parsing_request( void );
		int parsing_header(void);
		void parsing_body(void);
		int	check_request();
		void print_request( void );
		int Process_request();
		void SetReq_location(std::vector<std::string> &loc);
		int find_header();
		int check_startLine(std::string startLine);
		void find_host(std::string findHostLine);
		int find_content_info(std::string findContentLine);
		int check_doublon_keywords(std::vector<std::string> vec_kw);
		int check_lenght_body(std::string length);
		int parse_content_length(std::string length);
		int parse_body_length();
		//*************************************************************//
		//								SETTER						   //
		//*************************************************************//
		void SetMethod(std::string &str);
		void SetPort(std::string &str);
		void SetHost(std::string &str);
		void SetR_Location(std::string &str);
		void SetProtocol(std::string &str);
		void SetParsing(Parsing *parsing);
		void SetRequest(std::string request);
		void SetServer(Server *serv);
		void SetResponse(std::string Response);
		void SetHeader(std::string Header);
		void SetBody(std::string Body);
		void SetContentLength(unsigned long int ContentLength);
		void Set_recv_str( std::string str);
		void setBoundary( std::string bound);
		void setCgiStatus( std::string status);

		//*************************************************************//
		//								GETTER						   //
		//*************************************************************//

		std::string GetMethod( void) const;
		std::string GetPort( void) const;
		std::string GetHost( void) const;
		std::string GetR_Location( void) const;
		std::string GetProtocol( void) const;
		Parsing *GetParsing( void) const;
		Server *GetServer( void) const;
		std::string GetResponse( void) const;
		std::string GetHeader( void) const;
		std::string	Get_recv_str( void) const;
		std::string GetBody( void) const;
		std::string GetBoundary( void) const;
		unsigned long int GetContentLength( void) const;
		bool 		Get_All_recv( void) const;
		bool 		Get_header_recv( void) const;
		bool 		Get_favicon( void) const;
		//std::string GetRequest(char *request);


	private:
	std::string recv_str;
	std::string Method;
	std::string Response;
	std::string Port;
	std::string Host;
	std::string R_Location;
	std::string request;
	std::string Protocol;
	std::string Header;
	std::string Body;
	std::string Boundary;
	unsigned long int ContentLength;

	std::vector<std::string> request_split_line;
	std::vector<std::string> request_split_space;
	std::vector<std::string> location_split;
	std::vector<std::string> req_location;
	//std::vector< Location* > vec_location;
	bool b_method;
	bool bad_request;
	bool loc_found;
	bool header_recv;
	bool Content_length;
	bool All_recv;
	Location *loc;
	Cgi cgi;
	Parsing *parsing;
	Server *serv;
	int	index_server;
};

std::vector<std::string> cpsplit(std::string str, const char *sep);
void cpsplit_header(std::string str, const char *sep);
void print_vector(std::vector<std::string> vec);

#endif

