#include <iostream>

#include "ExecuteurCoup.h"
#include "../rules/RegleMouvementsMax.h"
#include "../rules/PassePasParMur.h"
#include "../rules/RegleAnnonceUnique.h"
#include "ApplicateurChoixChemin.h"
#include "ApplicateurChoixNbMouves.h"
#include "../Type.h"

ExecuteurCoup::ExecuteurCoup(){
    ruleEngine.addRule(new RegleMouvementsMax());//les new vont etre detruit par le ruleengine a la fin.
    ruleEngine.addRule(new PassePasParMur());
    ruleEngine.addRule(new RegleAnnonceUnique());
    
    applicateurs.insert({Type::choixNombreMouves, new ApplicateurChoixNbMouves});
    applicateurs.insert({Type::choixRoute, new ApplicateurChoixChemin});
}

ExecuteurCoup::~ExecuteurCoup(){
    delete applicateurs.at(Type::choixNombreMouves);
    applicateurs.erase(Type::choixNombreMouves);

    delete applicateurs.at(Type::choixRoute);
    applicateurs.erase(Type::choixRoute);
}

ExecuteurCoup& ExecuteurCoup::operator=(ExecuteurCoup& o){
    if (this == &o) {
        return *this;
    }

    // Libérer les anciens applicateurs
    for (auto& paire : applicateurs) {
        delete paire.second;
    }
    applicateurs.clear();

    ruleEngine = RuleEngine();
    ruleEngine.addRule(new RegleMouvementsMax());
    ruleEngine.addRule(new PassePasParMur());

    applicateurs.insert({Type::choixNombreMouves, new ApplicateurChoixNbMouves});
    applicateurs.insert({Type::choixRoute, new ApplicateurChoixChemin});

    return *this;
}

ExecuteurCoup::ExecuteurCoup(ExecuteurCoup&) : ExecuteurCoup(){
}


void ExecuteurCoup::executer(Coup& coup, Jeux& jeux){
    ResultatVerification resultat = ruleEngine.validate(jeux, coup);
    if (!resultat.valide){
        std::cout << "Coup non valide" << resultat.regleViolee;
    }

    auto iterateur = applicateurs.find(coup.getType());
    if(iterateur == applicateurs.end()){
        throw std::logic_error("pas d'applicateurs pour ce type de mouve");
    }
    iterateur->second->appliquer(coup, jeux);
    
}