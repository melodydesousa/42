#include "Cast.hpp"

Cast::Cast() : _char(0), _double(0), _float(0), _int (0), _infp(0), _infm(0), _nan(0), _limits(0) {
    return;
}

Cast::Cast(Cast const &cpy) : _char(cpy.getChar()), _double(cpy.getDouble()), _float(cpy.getFloat()), _int (cpy.getInt()),
		_infp(0), _infm(0), _nan(0), _limits(0) {
    *this = cpy;
    return;
}

Cast& Cast::operator=(Cast const &assign) {
    (void)assign;
    return *this;
}

Cast::~Cast() {
    return;
}

char Cast::getChar(void) const {
    return (this->_char);
}

int Cast::getInt(void) const {
    return (this->_int);
}

float Cast::getFloat(void) const {
    return (this->_float);
}

double Cast::getDouble(void) const {
    return (this->_double);
}

bool Cast::getIfInfp(void) const {
    return (this->_infp);
}

bool Cast::getIfInfm(void) const {
    return (this->_infm);
}

bool Cast::getIfNan(void) const {
    return (this->_nan);
}

bool Cast::getLimits(void) const {
    return (this->_limits);
}

void Cast::checkLiteral(std::string arg) {
	if (arg == "-inff" || arg == "-inf")
		this->_infm = true;
	else if (arg == "+inff" || arg == "+inf")
		this->_infp = true;
	else if (arg == "nanf" || arg == "nan")
		this->_nan = true;
	return;
}

void Cast::convert_limits(void) {
	if (this->_nan == true)
	{
		this->_float = std::numeric_limits<float>::quiet_NaN();
		this->_double = std::numeric_limits<double>::quiet_NaN();
	}
	else if (this->_infm == true)
	{
		this->_double = -1 * (std::numeric_limits<double>::infinity());
		this->_float = -1 * (std::numeric_limits<float>::infinity());
	}
	else if (this->_infp == true)
	{
		this->_float = std::numeric_limits<float>::infinity();
		this->_double = std::numeric_limits<double>::infinity();
	}
	return ;
}

void Cast::getType(std::string arg) {
	checkLiteral(arg);
	if (!this->_infm && !this->_infp && !this->_nan)
	{
		int point = 0;
		int f = 0;
		for (unsigned long int i = 0; arg[i]; i++)
		{
			if (arg[i] == '.')
				point++;
			else if (arg[i] == 'f')
				f++;
			else if (isdigit(arg[i]) == 0 && (arg[i] != '.')
				&& (arg[i] != 'f') && (arg[i] != '-'))
				throw FormatError();
		}
		if (point > 1 || f > 1)
			throw FormatError();
		if (point == 1)
		{
			if (arg[arg.length() - 1] == 'f')
				this->convert_float(arg);
			else
				this->convert_double(arg);
			return ;
		}
		this->convert_int(arg);
	}
	else
		convert_limits();
	return;
}

void Cast::convert(std::string arg) {
    if (arg.length() == 1)
    {
        if (isdigit(arg[0]) != 0)
            this->convert_int(arg);
        else
			this->convert_char(arg);
    }
	else
		getType(arg);
    return;
}

void Cast::convert_char(std::string arg) {
	this->_char = static_cast<char>(arg[0]);
	this->_int = static_cast<int>(this->_char);
	this->_double = static_cast<double>(this->_char);
	this->_float = static_cast<float>(this->_char); 
}

void Cast::convert_int(std::string arg) {
	this->_float = static_cast<float>(atof(arg.c_str()));
	this->_double = static_cast<double>(atof(arg.c_str()));
	if (this->_double <= INT_MAX && this->_double >= INT_MIN)
	{
		this->_int = static_cast<int>(atoi(arg.c_str()));
		this->_char = static_cast<char>(this->_int);
	}
	else
		this->_limits = true;
}

void Cast::convert_double(std::string arg) {
	this->_double = static_cast<double>(atof(arg.c_str()));
	this->_int = static_cast<int>(this->_double);
	this->_char = static_cast<char>(this->_double);
	this->_float = static_cast<float>(this->_double);
}

void Cast::convert_float(std::string arg) {
	this->_float = static_cast<float>(atof(arg.c_str()));
	this->_double = static_cast<double>(this->_float);
	this->_int = static_cast<int>(this->_float);
	this->_char = static_cast<char>(this->_float);
}

std::ostream& operator<<(std::ostream &out, Cast const &ref) {
    /************CHAR************/
	out << "char: ";
   	if (ref.getIfInfm() || ref.getIfInfp() || ref.getIfNan() || ref.getLimits() || ref.getChar() < 0 )
        out << "impossible\n";
	else if (!isprint(ref.getChar()))
        out << "Non displayable\n";
    else
		out << "'" << ref.getChar() << "'" << "\n";
    /***********INT************/
    out << "int: ";
	if (ref.getIfInfm() || ref.getIfInfp() || ref.getIfNan() || ref.getLimits())
        out << "impossible\n";
	else
		out << ref.getInt() << "\n";
    /***********FLOAT************/
    out << "float: " << ref.getFloat();
	if (!ref.getIfInfm() && !ref.getIfInfp() && !ref.getIfNan() && (ref.getInt() == ref.getFloat()))
		out << ".0";
	out << "f\n";
    /***********DOUBLE************/
    out << "double: " << ref.getDouble();
	if (!ref.getIfInfm() && !ref.getIfInfp() && !ref.getIfNan() && (ref.getInt() == ref.getDouble()))
		out << ".0";
    return out;
}
