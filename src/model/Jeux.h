#ifndef JEUX_H
#define JEUX_H
#include <vector>
#include "Joueur.h"
#include "PointsJoueurs.h"
#include "Coup.h"
#include "Tour.h"
#include "Plateaux.h"
#include "rules/RuleEngine.h"
#include "Cible.h"

class Jeux{
    private:
    std::vector<Joueur*> joueurs;
    std::vector<Tour*> tours;
    bool gameOver;
    PointsJoueurs points;
    Plateaux plateau;
    Cible choisirProchaineCible() const;
    public:
    Jeux();
    ~Jeux();
    Jeux(const Jeux& o);
    Jeux& operator=(const Jeux& o);

    Plateaux& getPlateau() { return plateau; }
    const Plateaux& getPlateau() const { return plateau; }
    const Tour& getCeTour() const;
    Tour& getCeTour();

    void prochainTour();
    /**
     * @brief avance l'etat du tour si besoin
     * doit etre appelé répetitivement ~1secondes
     * 
     */
    void avancerEtatTour();
    /**
     * @brief Enregistrer la victoire d'un seul tour.
     * 
     * la victoire est ajouté dans les points joueur et utilisé pour voir qui a gagné le jeux dans getGagnant().
     * @param gagnant 
     */
    void enregistrerVictoire(Joueur& gagnant);
    /**
     * @brief Renvoit le joueur gagnant après comparaison des points de chaque joueur.
     * Si deux joueurs sont en égalité, le premier joueur dans la list est pris.
     * 
     * @return Joueur& le gagnant
     */
    Joueur& getGagnant();


};

#endif