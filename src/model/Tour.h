#ifndef TOUR_H
#define TOUR_H

#include <vector>
#include <chrono>
#include "Joueur.h"
#include "Type.h"
#include "Cible.h"

struct MouvesJoueurs {
    Joueur* joueur;
    int nbMouves;
};
class Tour{
    private:
    int nbTour;
    std::vector<MouvesJoueurs> joueurs;//la liste des joueurs ordonnés par qui passe en premier. La liste contient que les joueurs qui ont proposé un temps
    Cible but;
    Type etat;//soit en mode choix temps soit en mode choix route ou les joueurs vont passer par leurs ordre dans la liste.
    std::chrono::steady_clock::time_point debutTemps;
    public:
    Tour(Cible but);
    /**
     * @brief commencer un compteur de 60 secondes.
     * 
     */
    void commencerHorloge();
    /**
     * @brief ajout d'une entree ou le joueur a choisit son nombre de mouves
     * 
     * @param joueur 
     * @param nbMouves le mouves que le joueur dit qu'il ne depassera pas
     */
    void ajoutJoueur(Joueur& joueur, int nbMouves);
    void prochainJoueur();//avance vers le joueurs d'apres.
    /**
     * @brief verifie si il y a des joueurs qui ont proposé un nombre de mouves
     * 
     * @return true la liste Tour::joueurs est vide et aucun joueur n'a proposé un temps.
     * @return false la liste contient au moin un element
     */
    bool pasMouvesPropose() const;
    Type getEtat() const;
    /**
     * @brief avoir le temps écoulé
     * le temps commence avec 60s dés que le tour est mis dans l'etat Type::choixNbMouves. Le constructeur mettra le jeux dans cet etat.
     * Lorsque le temps est 0 l'etat du tour changera automatiquement avec l'appel getTempsEcoule vers Type::choixRoute.
     * 
     * @return std::chrono::seconds le temps ecoulé de l'horloge.
     */
    int getTempsEcoule();
    int getMouvePlusFaible() const;
    /**
     * @brief Vérifie si le joueur a déjà annoncé un nombre de mouvements dans ce tour.
     */
    bool contientJoueur(const Joueur& joueur) const;


};
#endif