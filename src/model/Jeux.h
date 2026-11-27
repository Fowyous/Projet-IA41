#ifndef JEUX_H
#define JEUX_H
#include <vector>
#include "Joueur.h"
#include "PointsJoueurs.h"
#include "Coup.h"
#include "Tour.h"
#include "Plateaux.h"
#include "rules/RuleEngine.h"

class Jeux{
    private:
    std::vector<Joueur*> joueurs;
    std::vector<Tour*> tours;
    bool gameOver;
    PointsJoueurs points;
    Plateaux plateau;
    public:
    Jeux();
    ~Jeux();
    Jeux(const Jeux& o);
    Jeux& operator=(const Jeux& o);

    Plateaux& getPlateau() { return plateau; }
    const Plateaux& getPlateau() const { return plateau; }
    const Tour& getCeTour() const;

    void prochainTour();
    void avancerEtatTour();// a implementer
    Joueur& getGagnant();

};
#endif