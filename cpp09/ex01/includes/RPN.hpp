#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

class RPN
{

public:
    RPN();
    RPN(RPN const &cpy);
    ~RPN();
    RPN &operator=(RPN const &assign);

    void resolve(std::string av);
    void print(void);

private:
    std::stack<int> _result;
};

#endif