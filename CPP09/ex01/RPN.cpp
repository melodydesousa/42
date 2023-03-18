#include "RPN.hpp"

RPN::RPN() { }
RPN::RPN(RPN const &cpy) { *this = cpy;}
RPN::~RPN() { }
RPN& RPN::operator=(RPN const &assign) {
    (void)assign;
    return (*this);
}

void RPN::resolve(std::string av)
{
    for (int i = 0; av[i]; i++)
    {
        if (isdigit(av[i]))
        {
            int nb = av[i] - '0';
            _result.push(nb);
        }
        else if (av[i] == '+' || av[i] == '-' || av[i] == '*' || av[i] == '/')
        {
            int nb1 = _result.top();
            _result.pop();
            int nb2 = _result.top();
            _result.pop();
            if (av[i] == '+')
                _result.push(nb1 + nb2);
            else if (av[i] == '-')
                _result.push(nb2 - nb1);
            else if (av[i] == '*')
                _result.push(nb1 * nb2);
            else if (av[i] == '/')
                _result.push(nb1 / nb2);
        }
        else if (av[i] != ' ')
        {
            std::cout << "Error" << std::endl;
            return ;
        }
    }
    print();
}

void RPN::print(void)
{
    std::stack<int> tmp = _result;
    std::cout << tmp.top() << std::endl;
}