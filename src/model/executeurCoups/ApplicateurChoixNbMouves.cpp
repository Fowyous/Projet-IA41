#include "ApplicateurChoixNbMouves.h"

void ApplicateurChoixNbMouves::appliquer(Coup& coup, Jeux& jeux){
    Tour& tour = jeux.getCeTour();

    if (tour.pasMouvesPropose()){
        tour.commencerHorloge();
    }
    tour.ajoutJoueur(coup.getJoueur(), coup.getNbMouves());

}