#ifndef COUP_H
#define COUP_H

#include <vector>
#include "Joueur.h"
#include "Type.h"
#include "Directions.h"
#include "Pion.h"

class RegleMouvementsMax; // declaration a la place d'un #include pour eviter les inclusion circulaire. Coup est déja inclus par RegleMouvementsMax

class Coup{
    friend class RegleMouvementsMax;
    private:
    Joueur& joueur;
    int nbMouves;
    std::vector<Directions> chemin;
    Pion pion;
    Type type;

    std::vector<Directions> getChemin();
    int getNbMouves();
    Joueur& getJoueur();

    public:
    /**
     * @brief Faire un coup ou on choisit le nombre de mouves.
     * 
     * @param joueur 
     * @param nbMouves 
     */
    Coup(Joueur& joueur, int nbMouves);
    /**
     * @brief Faire un coup où on bouge un pion.
     * Le coup est pris même si le chemin ne respecte pas les regles (ex: passe a travers un murs ou plus de mouves que le nombre dit).
     * Il faut le validé avec le RuleEngine.
     * 
     * @param joueur Le joueur qui fait le coup
     * @param chemin Le chemin prix.(NORD, SUD, EST, OUEST)
     * @param pion Le pion bougé
     */
    Coup(Joueur& joueur, const std::vector<Directions> chemin, Pion& pion);
    ~Coup() = default; //pas besoin d'un destructeur la destruction du joueur ce fait par la classe Jeux
    Coup(const Coup& o);
    Coup& operator=(const Coup& o);

    void coupChoixNbMouves(Joueur& joueur, int nombre);
    /**
     * @brief Faire un coup où on bouge un pion.
     * Le coup est pris même si le chemin ne respecte pas les regles (ex: passe a travers un murs ou plus de mouves que le nombre dit).
     * Il faut le validé avec le RuleEngine.
     * 
     * @param joueur Le joueur qui fait le coup
     * @param chemin Le chemin prix.(NORD, SUD, EST, OUEST)
     * @param pion Le pion bougé
     */
    void coupChoixRoute(Joueur& joueur, const std::vector<Directions> chemin, Pion& pion);


};

#endif