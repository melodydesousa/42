#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include <iostream>
#include <vector>
#include "ATarget.hpp"
#include "ASpell.hpp"
#include "SpellBook.hpp"

class Warlock {
    public:
        Warlock(std::string const &name, std::string const &title);
        ~Warlock();

        std::string const & getName() const;
        std::string const & getTitle() const;
        void setTitle(std::string const &title);
        void introduce() const;

        void learnSpell(ASpell* spell);
        void forgetSpell(std::string spell_name);
        void launchSpell(std::string spell_name, ATarget const &target);

        SpellBook spellbook;

    private:
        Warlock();
        Warlock(Warlock const &cpy);
        Warlock& operator=(Warlock const &assign);
        std::string name;
        std::string title;
};

#endif
