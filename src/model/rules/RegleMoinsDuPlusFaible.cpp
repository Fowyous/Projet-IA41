#include "RegleMoinsDuPlusFaible.h"
#include "../Tour.h"
#include "../Jeux.h"

bool RegleMoinsDuPlusFaible::estApplicable(Jeux& jeux, Coup& coup) {
    if (jeux.getCeTour().getEtat() != Type::choixNombreMouves || (coup.getJoueur().getEtat() != Type::choixNombreMouves)){
        return false;
    }
    if (jeux.getCeTour().ontDejaProposeMouves()){//si c'est le premier a proposer le nb de mouves la regle ne le concerne pas.
        return true;
    }
    return false;
}

bool RegleMoinsDuPlusFaible::validate(Jeux& jeux, Coup& coup){
    if (coup.getNbMouves() <= jeux.getCeTour().getMouvePlusFaible()){
        return true;
    }
    return false;
}