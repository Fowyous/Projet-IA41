#ifndef PION_H
#define PION_H

#include "Couleur.h"

class Cible;

class Pion {
public:
    explicit Pion(Couleur couleur = Couleur::ROUGE);

    Couleur getCouleur() const { return couleur; }

    // Une cible active accepte les pions de sa couleur. Si elle est multicolore, tout pion convient.
    bool doitAllerCible(const Cible& cible) const;

private:
    Couleur couleur;
};

#endif
