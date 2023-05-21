#include "PmergeMe.hpp"

int main (int ac, char **av)
{
    std::vector<int> vec;
    std::vector<int>::iterator it;
    std::list<int> list;
    PmergeMe algo;

    if (ac < 2)
    {
        std::cout << "Error: too few arguments" << std::endl;
        return (0);
    }
    for (int i = 1; av[i]; )
    {
        if (av[i][0] == '\0')
        {
            std::cout << "Error" << std::endl;
            return (-1);
        }
        for (int j = 0; av[i][j]; j++)
        {
            if (!isdigit(av[i][j]))
            {
                std::cout << "Error" << std::endl;
                return (-1);
            }
        }
        unsigned long long tmp = atof(av[i]);
        if (tmp > INT_MAX)
        {
            std::cout << "Error" << std::endl;
            return (-1);
        }
        vec.push_back(atoi(av[i]));
        list.push_back(atoi(av[i]));
        i++;
    }
    std::cout << "Before: ";
	for (it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
    algo.setVector(vec);
    algo.setList(list);
    algo.Vector();
    algo.List();
    algo.printAfter();
    return (0);
}