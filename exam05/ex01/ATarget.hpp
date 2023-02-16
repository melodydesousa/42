#ifndef ATARGET_HPP
#define ATARGET_HPP

#include <iostream>
#include "ASpell.hpp"

class ASpell;

class ATarget {
    public:
        ATarget(std::string type);
        virtual ~ATarget();

        std::string const & getType() const;
        void getHitBySpell(ASpell const &spell) const;
        virtual ATarget* clone() const = 0;

    private:
        ATarget();
        ATarget(ATarget const &cpy);
        ATarget& operator=(ATarget const &assign);
        std::string type;
};

#endif
