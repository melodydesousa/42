#ifndef CAST_H
# define CAST_H

# include <iostream>
# include <stdexcept>
# include <cstring>
# include <climits>

class	Cast {
public:
	Cast(void);
	~Cast(void);
	Cast& operator=(Cast const &assign);
	Cast(Cast const &cpy);

	// void getType(std::string arg);
	void convert(std::string arg);

	char getChar(void) const;
	int	getInt(void) const;
	double getDouble(void) const;
	float getFloat(void) const;

	class NonDisplayable : public std::exception
	{
		public:
			virtual const char* what() const throw()
			{
				return ("Non displayable\n");
			}
	};

private:
	bool	_is_char;
	bool	_is_double;
	bool 	_is_float;
	bool	_is_int;
	char	_char;
	double	_double;
	float	_float;
	int		_int;

};

std::ostream& operator<<(std::ostream &out, Cast const &ref);


#endif
