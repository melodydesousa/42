#ifndef TARGETGENERATOR_HPP
#define TARGETGENERATOR_HPP

#include <iostream>
#include <vector>
#include "ATarget.hpp"

class TargetGenerator {
    public:
        TargetGenerator();
        ~TargetGenerator();

        void learnTargetType(ATarget* spell);
        void forgetTargetType(std::string const &type);
        ATarget* createTarget(std::string const &type);

    private:
        TargetGenerator(TargetGenerator const &cpy);
        TargetGenerator& operator=(TargetGenerator const &assign);
        std::vector<ATarget *> targets;
};

#endif
