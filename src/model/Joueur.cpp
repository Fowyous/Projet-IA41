#include "Joueur.h"
Joueur::Joueur(std::string nom){
    if (nom == ""){
        throw std::runtime_error("Constructeur Joueur(nom) initié sans nom");
    }
    this->nom = nom;
    etat = Type::choixNombreMouves;
}

bool Joueur::operator==(const Joueur& o) const{
    return nom == o.nom;
}

Type Joueur::getEtat() const{
    return etat;
}
