#include "TargetGenerator.hpp"

TargetGenerator::~TargetGenerator(){
   	std::vector<ATarget *>::iterator it;
	for (it = targets.begin();it != targets.end();++it)
	{
		delete *it;
	}
	targets.clear();
}

TargetGenerator::TargetGenerator(){}

TargetGenerator::TargetGenerator(TargetGenerator const &cpy){
    *this = cpy;
}
TargetGenerator& TargetGenerator::operator=(TargetGenerator const &assign){
    (void)assign;
    return *this;
}

void TargetGenerator::learnTargetType(ATarget* target){
    std::vector<ATarget*>::iterator it;
    
    if (target)
    {
        for (it = targets.begin(); it != targets.end(); ++it)
        {
            if ((*it)->getType() == target->getType())
                return;
        }
        targets.push_back(target->clone());
    }

}
void TargetGenerator::forgetTargetType(std::string const & type){
    std::vector<ATarget*>::iterator it;
    
   for (it = targets.begin(); it != targets.end(); ++it)
    {
        if ((*it)->getType() == type)
        {
            delete *it;
            targets.erase(it);
            return;
        }
    }
}

ATarget* TargetGenerator::createTarget(std::string const &type){
    std::vector<ATarget*>::iterator it;
    
   for (it = targets.begin(); it != targets.end(); ++it)
    {
        if ((*it)->getType() == type)
        {
            return(*it);
        }
    }
    return (NULL);
}