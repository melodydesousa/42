#include "Warlock.hpp"

Warlock::Warlock(std::string const &name, std::string const &title) : name(name), title(title) {
    std::cout << name << ": This looks like another boring day.\n";
}

Warlock::~Warlock(){
	std::vector<ASpell *>::iterator it;
	for (it = book.begin();it != book.end();++it)
	{
		delete *it;
	}
	book.clear();
    std::cout << name << ": My job here is done!\n";
}

std::string const & Warlock::getName() const{return(this->name);}

std::string const & Warlock::getTitle() const{return(this->title);}

void Warlock::setTitle(std::string const &title){
    this->title = title;
}

void Warlock::introduce() const {
    std::cout << getName() << ": I am " << getName() << ", " << getTitle() << "!\n";
}

Warlock::Warlock(){}

Warlock::Warlock(Warlock const &cpy){
    *this = cpy;
}
Warlock& Warlock::operator=(Warlock const &assign){
    this->name = assign.name;
    this->title = assign.title;
    return *this;
}

void Warlock::learnSpell(ASpell* spell){
    std::vector<ASpell*>::iterator it;
    
    if (spell)
    {
        for (it = book.begin(); it != book.end(); ++it)
        {
            if ((*it)->getName() == spell->getName())
                return;
        }
        book.push_back(spell->clone());
    }

}
void Warlock::forgetSpell(std::string spell_name){
    std::vector<ASpell*>::iterator it;
    
   for (it = book.begin(); it != book.end(); ++it)
    {
        if ((*it)->getName() == spell_name)
        {
            delete *it;
            book.erase(it);
            return;
        }
    }
}

void Warlock::launchSpell(std::string spell_name, ATarget const &target){
    std::vector<ASpell*>::iterator it;
    
   for (it = book.begin(); it != book.end(); ++it)
    {
        if ((*it)->getName() == spell_name)
        {
            (*it)->launch(target);
            return;
        }
    }
}
