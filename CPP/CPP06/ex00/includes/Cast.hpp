#ifndef CAST_H
# define CAST_H

# include <iostream>
# include <stdexcept>
# include <cstring>
# include <cstdlib>
# include <limits>
# include <climits>
# include <cmath>

class	Cast {
public:
	Cast(void);
	~Cast(void);
	Cast& operator=(Cast const &assign);
	Cast(Cast const &cpy);

	void getType(std::string arg);
	void checkLiteral(std::string arg);
	void convert(std::string arg);
	void convert_limits(void);

	void convert_char(std::string arg);
	void convert_int(std::string arg);
	void convert_float(std::string arg);
	void convert_double(std::string arg);

	char getChar(void) const;
	int	getInt(void) const;
	double getDouble(void) const;
	float getFloat(void) const;
	bool	getIfInfp(void) const;
	bool	getIfInfm(void) const;
	bool	getIfNan(void) const;
	bool	getLimits(void) const;

	class FormatError : public std::exception
	{
		public:
			virtual const char* what() const throw()
			{
				return ("Error: format\n");
			}
	};

private:
	char	_char;
	double	_double;
	float	_float;
	int		_int;
	bool 	_infp;
	bool 	_infm;
	bool 	_nan;
	bool	_limits;
};

std::ostream& operator<<(std::ostream &out, Cast const &ref);


#endif
