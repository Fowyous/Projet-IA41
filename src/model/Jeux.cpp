#include "Jeux.h"
#include "PointsJoueurs.h"
#include "Tour.h"
#include "Joueur.h"
#include "rules/RuleEngine.h"

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

Jeux::Jeux(const Jeux& o) : gameOver(o.gameOver), points(o.points){
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

void Jeux::appliqueCoup(Coup coup){
    ResultatVerification resultat = enginRegles.validate(*this, coup);
    if (resultat.valide == true){
        //a implementer.
    }
}