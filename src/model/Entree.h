#ifndef ENTREE_H
#define ENTREE_H

#include "Joueur.h"

class Entree{
    private:
    int nbTour;
    Joueur& joueurGagnant;
    public:
    Joueur& getJoueurGagnant();
    Entree(int nbTour, Joueur& joueurGagnant) : nbTour(nbTour), joueurGagnant(joueurGagnant){}
};

#endif