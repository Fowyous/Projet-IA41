#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
#include <stdexcept>
#include "Type.h"
class Joueur{
    private:
    Type etat;
    std::string nom;//pas de nom dupliqué autorisé. La verification doit etre faite a la classe Jeux pour ajoutJoueur.
    int points;

    public :
    Joueur(std::string nom);
    ~Joueur() = default;
    Joueur(const Joueur& o) = default;
    Joueur& operator=(const Joueur& o) = default;

    bool operator==(const Joueur& o) const;
    Type getEtat() const;
};
#endif