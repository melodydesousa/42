#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Request.hpp"
#define BUFFER_SIZE 10240

class Client
{
	public:
		Client();
		Client(int socket);
		~Client();
		void clear();
		int fd_ready_IO( int i);
		int find_header();
		int ft_recv( int i);
		void	check_send(int rc);
		void	check_recv(int rc);
		void	bad_request(std::string status);
		int check_lenght_body();
		void Set_end_co( bool end_co);
		void Set_allowed_send( bool end_co);
		void Set_All_send( bool send);
		bool Get_end_co( void ) const;
		bool Get_All_send( void ) const;
		bool Get_All_recv();
		bool Get_php_to( void) const;
		bool Get_header_recv();
		Request Get_request();
		long long 					get_send_body_size(void) const;
		
		bool Get_favicon( void) const;
		bool GetWait( void) const;
		void parse_content_length(std::string str);
		int parse_transfer_encoding(std::string str);
		void parse_body_length();
		time_t Get_timer();
		void Set_timer(time_t timer);
		void set_parsing(Parsing *parsing);
		int ft_send( int i);
	private:

	bool	header_recv;
	bool	Content_length;
	bool	All_recv;
	bool	All_send;
	bool	Wait;
	bool	allowed_send;
	bool end_co;
	char	buffer_in[BUFFER_SIZE];
	std::string recv_str;
	Parsing *parsing;
	std::string send_str;
	std::vector<std::string> request_line;
	long long len_recv;
	unsigned long int length_expected;
	long long len_send;
	int socket;
	Request request;
	time_t timer;
};

std::string example_post();

#endif
