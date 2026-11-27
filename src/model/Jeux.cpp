#include "Jeux.h"
#include "PointsJoueurs.h"
#include "Tour.h"
#include "Joueur.h"
#include "rules/RuleEngine.h"
#include "rules/PassePasParMur.h"
#include <memory>

namespace {
void ajouterRegleDeplacement(RuleEngine& moteur) {
    auto regle = std::make_unique<PassePasParMur>();
    moteur.addRule(*regle);
    // Le moteur prend en charge la destruction après l'enregistrement.
    regle.release();
}
}

Jeux::Jeux() : gameOver(false), points(){
    ajouterRegleDeplacement(enginRegles);
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
    ajouterRegleDeplacement(enginRegles);
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