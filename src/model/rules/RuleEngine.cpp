#include "RuleEngine.h"
#include "Rule.h"

RuleEngine::~RuleEngine(){
    for (Rule* rule : rules){
        delete rule;
    }
}

void RuleEngine::addRule(Rule& rule){
    rules.push_back(&rule);
}

ResultatVerification RuleEngine::validate(Jeux& jeux, Coup& coup){
    for (const auto& rule : rules){
        Rule& regle = *rule;
        if (!regle.estApplicable(jeux, coup)){ 
            continue;
        }
        if (!regle.validate(jeux, coup)){
            return {false, &regle};
        }
    }
    return {true, nullptr};
}