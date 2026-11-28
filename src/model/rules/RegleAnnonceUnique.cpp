#include "RegleAnnonceUnique.h"
#include "../Jeux.h"
#include "../Coup.h"
#include "../Tour.h"
#include "../Type.h"

bool RegleAnnonceUnique::estApplicable(Jeux& jeux, Coup& coup) {
    (void)jeux;
    return coup.getType() == choixNombreMouves;
}

bool RegleAnnonceUnique::validate(Jeux& jeux, Coup& coup) {
    Tour& tour = jeux.getCeTour();
    return !tour.contientJoueur(coup.getJoueur());
}
