#include "ATarget.hpp"

ATarget::ATarget(std::string type) : type(type) {
}

ATarget::~ATarget(){
}

std::string const & ATarget::getType() const{return(this->type);}

void ATarget::getHitBySpell(ASpell const &spell) const {
    std::cout << getType() << " has been " << spell.getEffects() << "!\n";
}

ATarget::ATarget(){}

ATarget::ATarget(ATarget const &cpy){
    *this = cpy;
}
ATarget& ATarget::operator=(ATarget const &assign){
    this->type = assign.type;
    return *this;
}