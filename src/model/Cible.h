#ifndef CIBLE_H
#define CIBLE_H

#include "Couleur.h"
#include "Forme.h"

class Cible {
public:
    Cible(Couleur couleur, Forme forme, bool but = true)
        : couleur(couleur), forme(forme), but(but) {}

    Couleur getCouleur() const { return couleur; }
    Forme getForme() const { return forme; }
    bool estBut() const { return but; }
    void setBut(bool active) { but = active; }

private:
    Couleur couleur;
    Forme forme;
    bool but;  // Vrai si cette cible est l'objectif du tour.
};

#endif
