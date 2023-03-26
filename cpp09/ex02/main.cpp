#include "PmergeMe.hpp"

int main (int ac, char **av)
{
    std::vector<int> vec;
    std::vector<int>::iterator it;
    std::list<int> list;
    PmergeMe merge;

    if (ac < 2)
        std::cout << "Error: too few arguments" << std::endl;
    for (int i = 1; av[i]; )
    {
        for (int j = 0; av[i][j]; j++)
        {
            if (!isdigit(av[i][j]))
            {
                std::cout << "Error" << std::endl;
                return (-1);
            }
        }
        if (atof(av[i]) > INT_MAX)
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
    merge.setVector(vec);
    merge.setList(list);
    merge.sortVector();
    merge.sortList();
    merge.printAfter();
    return (0);
}