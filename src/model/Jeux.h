#ifndef JEUX_H
#define JEUX_H
#include <vector>
#include "Joueur.h"
#include "PointsJoueurs.h"
#include "Coup.h"
#include "Tour.h"

class Jeux{
    private:
    std::vector<Joueur*> joueurs;
    std::vector<Tour*> tours;
    bool gameOver;
    PointsJoueurs points;
    public:
    Jeux();
    ~Jeux();
    Jeux(const Jeux& o);
    Jeux& operator=(const Jeux& o);

    const Tour& getCeTour() const;

    void prochainTour();
    void appliqueCoup(Coup coup);
    Joueur& getGagnant();

};
#endif