#ifndef BRAIN_H
# define BRAIN_H

# include <iostream>

class	Brain {

public:
	Brain(void);
	Brain(Brain const &copy);
	~Brain(void);
	Brain& operator=(Brain const &Brain);

	const std::string &getIdea(int index) const;
	void setIdeas(int index, std::string idea);

private:
	std::string _ideas[100];
};

#endif
