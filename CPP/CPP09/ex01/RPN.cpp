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
            if (isdigit(av[i + 1]))
            {
                std::cout << "Error: number must be between 0 and 9" << std::endl;
                return ;
            }
            int nb = av[i] - '0';
            _result.push(nb);
        }
        else if (av[i] == '+' || av[i] == '-' || av[i] == '*' || av[i] == '/')
        {
            if (_result.size() < 2)
            {
                std::cout << "Error: bad input" << std::endl;
                return ;
            }
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
            {
                if (nb1 == 0)
                {
                    std::cout << "Error: division by 0 not possible" << std::endl;
                    return ;
                }
                _result.push(nb2 / nb1);
            }
        }
        else if (av[i] != ' ')
        {
            std::cout << "Error: bad input" << std::endl;
            return ;
        }
    }
    print();
}

void RPN::print(void)
{
    std::stack<int> tmp = _result;
    if (tmp.size() > 1)
    {
        std::cout << "Error: more than one number in stack" << std::endl;
        return ;
    }
    std::cout << tmp.top() << std::endl;
}