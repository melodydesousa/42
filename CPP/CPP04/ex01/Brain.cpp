#include "Brain.hpp"

Brain::Brain(void) {
	std::cout << "Default Brain constructor called\n";
	for (int i = 0; i < 100; i++) {
		if (i % 2 == 0)
			_ideas[i] = "Good idea";
		else
			_ideas[i] = "Bad idea";
	}
}

Brain::Brain(Brain const &copy) {
	std::cout << "Copy Brain constructor called\n";
	*this = copy;
}

Brain& Brain::operator=(Brain const &brain) {
	std::cout << "Brain operator = called\n";
	if (this != &brain)
	{
		for (int i = 0; i < 100; i++) {
			this->_ideas[i] = brain._ideas[i];
		}
	}
	return *this;
}

Brain::~Brain(void) {
	std::cout << "Destructor Brain called\n";
}

const std::string& Brain::getIdea(int index) const {
	return (this->_ideas[index]);
}

void Brain::setIdeas(int index, std::string idea) {
	this->_ideas[index] = idea;
}
