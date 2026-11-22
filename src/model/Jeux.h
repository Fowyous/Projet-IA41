#ifndef JEUX_H
#define JEUX_H
#include <vector>
#include "Joueur.h"
#include "PointsJoueurs.h"
#include "Coup.h"
#include "Tour.h"
#include "rules/Rule.h"
class Jeux{
    private:
    std::vector<Joueur*> joueurs;
    std::vector<Tour*> tours;
    bool gameOver;
    PointsJoueurs points;
    Tour& getCeTour();
    public:
    void prochainTour();
    void appliqueCoup(Coup coup);
    Joueur& getGagnant();

};
#endif