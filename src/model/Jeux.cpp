#include "Jeux.h"
#include "PointsJoueurs.h"
#include "Tour.h"
#include "Joueur.h"
#include "rules/RuleEngine.h"
#include "rules/PassePasParMur.h"
#include <memory>



Jeux::Jeux() : gameOver(false), points(){
}

Jeux::~Jeux(){
    for (Joueur* joueur : joueurs){
        delete joueur;
    }
    for (Tour* tour : tours){
        delete tour;
    }
}

Jeux::Jeux(const Jeux& o) : gameOver(o.gameOver), points(o.points), plateau(o.plateau){
    for (Joueur* joueur : joueurs){
        delete joueur;
    }
    joueurs.clear();
    joueurs.reserve(o.joueurs.size());
    for (const Joueur* ojoueur : o.joueurs){
        joueurs.push_back(ojoueur ? new Joueur(*ojoueur) : nullptr);
    }
    for (Tour* tour : tours){
        delete tour;
    }
    tours.clear();
    tours.reserve(o.tours.size());
    for (const Tour* otour : o.tours){
        tours.push_back(otour ? new Tour(*otour) : nullptr);
    }
}

const Tour& Jeux::getCeTour() const{
    return *tours.back();
}

Tour& Jeux::getCeTour(){
    return *tours.back();
}