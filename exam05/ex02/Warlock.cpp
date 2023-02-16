#include "Warlock.hpp"

Warlock::Warlock(std::string const &name, std::string const &title) : name(name), title(title) {
    std::cout << name << ": This looks like another boring day.\n";
}

Warlock::~Warlock(){
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

Warlock::Warlock() {}

Warlock::Warlock(Warlock const &cpy){
    *this = cpy;
}
Warlock& Warlock::operator=(Warlock const &assign){
    this->name = assign.name;
    this->title = assign.title;
    return *this;
}

void Warlock::learnSpell(ASpell* spell){
    spellbook.learnSpell(spell);
}

void Warlock::forgetSpell(std::string spell_name){
   spellbook.forgetSpell(spell_name);
}

void Warlock::launchSpell(std::string spell_name, ATarget const &target){
   ASpell* tmp = spellbook.createSpell(spell_name);
   if (tmp)
    tmp->launch(target);
}
