#include "Joueur.h"
Joueur::Joueur(std::string nom){
    if (nom == ""){
        throw std::runtime_error("Constructeur Joueur(nom) initié sans nom");
    }
    this->nom = nom;
}

bool Joueur::operator==(const Joueur& o) const{
    return nom == o.nom;
}

Type Joueur::getEtat() const{
    return etat;
}

Joueur::Joueur(const Joueur& o) : etat(o.etat), nom(o.nom), points(o.points){
}