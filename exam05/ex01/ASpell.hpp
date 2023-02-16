#ifndef ASPELL_HPP
#define ASPELL_HPP

#include <iostream>
#include "ATarget.hpp"

class ATarget;

class ASpell {
    public:
        ASpell(std::string name, std::string effects);
        virtual ~ASpell();

        std::string getName() const;
        std::string getEffects() const;

        virtual ASpell* clone() const = 0;
        void launch(ATarget const &target) const;

    private:
        ASpell();
        ASpell(ASpell const &cpy);
        ASpell& operator=(ASpell const &assign);
        std::string name;
        std::string effects;
};

#endif
