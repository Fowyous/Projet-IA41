#include "../Type.h"
#include "ApplicateurCoup.h"
#include "../rules/RuleEngine.h"
#include <map>

class ExecuteurCoup{
    private:
    RuleEngine ruleEngine;
    std::map<Type, ApplicateurCoup*> applicateurs;

    public:
    ExecuteurCoup();
    ~ExecuteurCoup();
    ExecuteurCoup(ExecuteurCoup& o);
    ExecuteurCoup& operator=(ExecuteurCoup& o);

    void executer(Coup& coup, Jeux& jeux);


};