#include "Cast.hpp"

Cast::Cast() : _is_char(false), _is_double(false), _is_float(false), 
    _is_int(false), _char(0), _double(0), _float(0), _int (0) {
    return;
}

Cast::Cast(Cast const &cpy) : _is_char(cpy._is_char), _is_double(cpy._is_double), _is_float(cpy._is_float), 
    _is_int(cpy._is_int), _char(cpy.getChar()), _double(cpy.getDouble()), _float(cpy.getFloat()), _int (cpy.getInt()) {
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

// void Cast::getType(std::string arg) {
//    return;
// }

void Cast::convert(std::string arg) {
    if (arg.length() == 1)
    {
        if (arg[0] >= '0' && arg[0] <= '9')
        {
            this->_is_int = true;
            this->_int = static_cast<int>(std::atoi(arg.c_str()));
            this->_char = static_cast<char>(this->_int);
            this->_double = static_cast<double>(this->_int);
            this->_float = static_cast<float>(this->_int);           
        }
        else
        {
            this->_is_char = true;
            this->_char = static_cast<char>(arg[0]);
            this->_int = static_cast<int>(this->_char);
            this->_double = static_cast<double>(this->_char);
            this->_float = static_cast<float>(this->_char);       
        }
    }
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

std::ostream& operator<<(std::ostream &out, Cast const &ref) {
    // out << "char: ";
    out << "char: " << ref.getChar() << "\n";

    if (ref.getChar() == '\0')
        out << "Not displayable\n";
    out << "int: " << ref.getInt() << "\n";
    out << "float: " << ref.getFloat() << "\n";
    out << "double: " << ref.getDouble() << "\n";
    return out;
}
