#ifndef COUP_H
#define COUP_H

#include <vector>
#include "Joueur.h"
#include "Type.h"
#include "Directions.h"
#include "Pion.h"
#include "rules/RegleMouvementsMax.h"
class Coup{
    friend class RegleMouvementsMax;
    private:
    Joueur joueur;
    Type type;
    int nbMouves;
    std::vector<Directions> chemin;
    Pion pion;

    int getNbMouves();
    std::vector<Directions> getChemin();
    public:
    void coupChoixNbMouves(Joueur joueur, int nombre);
    /**
     * @brief Faire un coup où on bouge un pion.
     * Le coup est pris même si le chemin ne respecte pas les regles (ex: passe a travers un murs ou plus de mouves que le nombre dit).
     * Il faut le validé avec le RuleEngine.
     * 
     * @param joueur Le joueur qui fait le coup
     * @param chemin Le chemin prix.(NORD, SUD, EST, OUEST)
     * @param pion Le pion bougé
     */
    void coupChoixRoute(Joueur joueur, const std::vector<Directions> chemin, Pion pion);


};

#endif