#include "RegleMouvementsMax.h"
#include "../Tour.h"

bool RegleMouvementsMax::estApplicable(Jeux& jeux, Coup& coup) {
    if (jeux.getCeTour().getEtat() != Type::choixRoute || (coup.getJoueur().getEtat() != Type::choixRoute)){
        return false;
    }
    return true;
}

bool RegleMouvementsMax::validate(Jeux&, Coup& coup){
    if(coup.getNbMouves() < coup.getChemin().size()){
        return false;
    }
    return true;
}