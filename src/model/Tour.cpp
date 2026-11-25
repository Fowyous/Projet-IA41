#include "Tour.h"
#include <chrono>
#include <algorithm>

Type Tour::getEtat() const{
    return etat;
}

Tour::Tour(Cible but) :  but(but), etat(Type::choixNombreMouves), debutTemps(std::chrono::steady_clock::now()){}

int Tour::getTempsEcoule(){
    using namespace std::chrono;

    auto ecoule = duration_cast<seconds>(steady_clock::now() - debutTemps).count();
    if (ecoule <= 0){
        etat = Type::choixRoute;
        return 0;
    }
    return static_cast<int>(ecoule);
}

void Tour::ajoutJoueur(Joueur& joueur, int nbMouves){
    auto position = std::lower_bound(
        joueurs.begin(),
        joueurs.end(),
        nbMouves,
        [](const MouvesJoueurs& entree, int nombre) {
            return entree.nbMouves < nombre;
        }
    );

    joueurs.insert(position, {&joueur, nbMouves});
}

void Tour::prochainJoueur(){
    joueurs.erase(joueurs.begin());
}

bool Tour::ontDejaProposeMouves() const{
    return !joueurs.empty();
}

int Tour::getMouvePlusFaible() const{
    return joueurs.front().nbMouves;
}