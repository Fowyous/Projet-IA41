#include "RegleMouvementsMax.h"
#include "../Tour.h"
#include "../Jeux.h"

bool RegleMouvementsMax::estApplicable(Jeux& jeux, Coup& coup) {
    if (jeux.getCeTour().getEtat() != Type::choixRoute || (coup.getJoueur().getEtat() != Type::choixRoute)){
        return false;
    }
    return true;
}

bool RegleMouvementsMax::validate(Jeux&, Coup& coup){
    const int nbMouvements = coup.getNbMouves();
    if(nbMouvements < 0 || static_cast<std::size_t>(nbMouvements) < coup.getChemin().size()){
        return false;
    }
    return true;
}