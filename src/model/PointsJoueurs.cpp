#include <vector>
#include "PointsJoueurs.h"
#include "Entree.h"

PointsJoueurs::~PointsJoueurs(){
    for (Entree* entree : entrees){
        delete entree;   
    }
}

void PointsJoueurs::sauvegardePoints(int nbTour, Joueur& joueurGagnant){
    entrees.push_back(new Entree(nbTour, joueurGagnant));
}

int PointsJoueurs::getReussiteTotal(Joueur& joueur){
    int pointsTotal;
    for (Entree* entree : entrees){
        if (joueur == entree->getJoueurGagnant()){
            pointsTotal++;
        }
    }
    return pointsTotal;
}