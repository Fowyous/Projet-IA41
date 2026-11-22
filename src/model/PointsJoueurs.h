#ifndef POINTSJOUEURS_H
#define POINTSJOUEURS_H

#include <vector>
#include "Entree.h"
#include "Joueur.h"
class PointsJoueurs{
    private:
    std::vector<Entree*> entrees;
    public:
    ~PointsJoueurs();
    /**
     * On ajoute a la base de donnee de points de joueurs les points recus pour un tour
     * La seule information necessaire pour cela c'est quel joueur a gagné ce tour.
     * 
     * @param nbTour Le tour qu'on veut ajouter dans la base
     * @param joueurGagnant qui a gagné le tour.
     */
    void sauvegardePoints(int nbTour, Joueur& joueurGagnant);

    /**
     * Obtenir la reussite total dans le jeux pour un seul joueur.
     * 
     * @param joueur Le joueur qu'on veut avoir sa reussite.
     * @return Le nombre de reussite (points) pour ce joueur.
     */
    int getReussiteTotal(Joueur& joueur);

};

#endif