#include "Joueur.h"
Joueur::Joueur(std::string nom){
    if (nom == "")
    {
        throw std::runtime_error("Constructeur Joueur(nom) initié sans nom");
    }
    this->nom = nom;
}
