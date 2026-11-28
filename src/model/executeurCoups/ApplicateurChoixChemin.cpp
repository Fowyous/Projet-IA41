#include "ApplicateurChoixChemin.h"

void ApplicateurChoixChemin::appliquer(Coup& coup, Jeux& jeux){
    Plateaux& plateau = jeux.getPlateau();

    for (Directions direction : coup.getChemin()) {
        plateau.deplacer(coup.getPion(), direction);
    }
    jeux.enregistrerVictoire(coup.getJoueur());
    jeux.prochainTour();
    
}