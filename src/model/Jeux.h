#ifndef JEUX_H
#define JEUX_H
#include <vector>
#include "Joueur.h"
#include "PointsJoueurs.h"
#include "Coup.h"
class Jeux{
    private:
    std::vector<Joueur*> joueurs;
    bool gameOver;
    PointsJoueurs points;
    public:
    void prochainTour();
    void appliqueCoup(Coup coup);
    Joueur& getGagnant();

};
#endif