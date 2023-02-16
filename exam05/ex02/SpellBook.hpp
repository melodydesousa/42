#ifndef SPELLBOOK_HPP
#define SPELLBOOK_HPP

#include <iostream>
#include <vector>
#include "ASpell.hpp"

class SpellBook {
    public:
        SpellBook();
        ~SpellBook();

        void learnSpell(ASpell* spell);
        void forgetSpell(std::string const &spell_name);
        ASpell* createSpell(std::string const &spell_name);

    private:
        SpellBook(SpellBook const &cpy);
        SpellBook& operator=(SpellBook const &assign);
        std::vector<ASpell *> book;
};

#endif