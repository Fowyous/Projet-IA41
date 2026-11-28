#include "Tour.h"
#include <chrono>
#include <algorithm>

Type Tour::getEtat() const{
    return etat;
}

Tour::Tour(Cible but) :  but(but), etat(Type::choixNombreMouves){}

void Tour::commencerHorloge(){
    debutTemps = std::chrono::steady_clock::now();
}
int Tour::getTempsEcoule(){
    using namespace std::chrono;

    if (debutTemps.time_since_epoch() == steady_clock::duration::zero()){
        throw std::logic_error("demande de temps ecoulé avant initialisation de l'horloge");
    }

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

bool Tour::pasMouvesPropose() const{
    return !joueurs.empty();
}

int Tour::getMouvePlusFaible() const{
    return joueurs.front().nbMouves;
}

bool Tour::contientJoueur(const Joueur& joueur) const {
    for (const MouvesJoueurs& entree : joueurs) {
        if (*entree.joueur == joueur) {
            return true;
        }
    }
    return false;
}
