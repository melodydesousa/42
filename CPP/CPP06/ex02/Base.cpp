#include "Base.hpp"

Base::~Base() {
	return;
}

Base * generate(void) {
	Base *random = NULL;
	std::srand(time(0));
	if (std::rand() % 3 == 0)
		random = new A;
	else if (std::rand() % 3 == 1)
		random = new B;
	else
		random = new C;
	return (random);
}

void identify(Base* p) {
	A* a = dynamic_cast<A*>(p);
	B* b = dynamic_cast<B*>(p);
	C* c = dynamic_cast<C*>(p);

	if (a)
		std::cout << "* class is A *\n";
	else if (b)
		std::cout << "* class is B *\n";
	else if (c)
		std::cout << "* class is C *\n";
}

void identify(Base& p) {
	try 
	{
		A& a = dynamic_cast<A&>(p);
		(void)a;
		std::cout << "& class is A &\n";
	}
	catch (std::exception) {}

	try 
	{
		B& b = dynamic_cast<B&>(p);
		(void)b;
		std::cout << "& class is B &\n";
	}
	catch (std::exception) {}

	try 
	{
		C& c = dynamic_cast<C&>(p);
		(void)c;
		std::cout << "& class is C &\n";
	}
	catch (std::exception) {}
}