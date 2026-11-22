#include "RegleMouvementsMax.h"

bool RegleMouvementsMax::estApplicable(Jeux& jeux, Coup& coup){//a implementer
}

bool RegleMouvementsMax::validate(Jeux& jeux, Coup& coup){
    if(coup.getNbMouves() < coup.getChemin().size()){
        return false;
    }
    return true;
}