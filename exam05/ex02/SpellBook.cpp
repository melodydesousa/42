#include "SpellBook.hpp"

SpellBook::~SpellBook(){
   	std::vector<ASpell *>::iterator it;
	for (it = book.begin();it != book.end();++it)
	{
		delete *it;
	}
	book.clear();
}

SpellBook::SpellBook(){}

SpellBook::SpellBook(SpellBook const &cpy){
    *this = cpy;
}
SpellBook& SpellBook::operator=(SpellBook const &assign){
    (void)assign;
    return *this;
}

void SpellBook::learnSpell(ASpell* spell){
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
void SpellBook::forgetSpell(std::string const & spell_name){
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

ASpell* SpellBook::createSpell(std::string const &spell_name){
    std::vector<ASpell*>::iterator it;
    
   for (it = book.begin(); it != book.end(); ++it)
    {
        if ((*it)->getName() == spell_name)
        {
            return(*it);
        }
    }
    return (NULL);
}