#include "MutantStack.hpp"
#include "colors.h"

int main()
{
	std::cout << YELLOW "SUBJECT TEST" RESET << std::endl;
	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);
	std::cout << "top = " << mstack.top() << std::endl;
	mstack.pop();
	std::cout << "size after pop = " << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	//[...]
	mstack.push(0);
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << "elem = " << *it << std::endl;
		++it;
	}
	std::cout << "final size = " << mstack.size() << std::endl;
	std::stack<int> s(mstack);
	std::cout << "size copy = " << s.size() << std::endl;

//////////////////////////////////////////////////////////////

	std::cout << YELLOW "LIST TEST" RESET << std::endl;
	std::list<int> mlist;
	mlist.push_back(5);
	mlist.push_back(17);
	std::cout << "top = " << mlist.back() << std::endl;
	mlist.pop_back();
	std::cout << "size after pop = " << mlist.size() << std::endl;
	mlist.push_back(3);
	mlist.push_back(5);
	mlist.push_back(737);
	//[...]
	mlist.push_back(0);
	std::list<int>::iterator it1 = mlist.begin();
	std::list<int>::iterator ite1 = mlist.end();
	++it1;
	--it1;
	while (it1 != ite1)
	{
		std::cout << "elem = " << *it1 << std::endl;
		++it1;
	}
	std::cout << "final size = " << mlist.size() << std::endl;
	std::list<int> slist(mlist);
	std::cout << "size copy = " << slist.size() << std::endl;

	return 0;
}