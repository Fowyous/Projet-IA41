#ifndef PLATEAUX_H
#define PLATEAUX_H

#include "Case.h"
#include <array>

class Plateaux {
public:
    static constexpr int TAILLE = 16;
    Plateaux();

    // (0, 0) est en haut à gauche. Une coordonnée hors grille lève std::out_of_range.
    const Case& getCase(int x, int y) const;

    // Entre deux cases, un seul appel suffit pour bloquer le passage dans les deux sens.
    void ajouterMur(int x, int y, Directions direction);
    void placerCible(int x, int y, Cible cible);

    // Un seul pion par couleur et par case. Renvoie false si le placement est impossible.
    bool placerPion(int x, int y, Pion pion);
    const Case* trouverPion(Couleur couleur) const;

    // Le pion traverse les cibles et s'arrête sur la dernière case libre avant un mur ou un pion.
    // Renvoie false si le pion est absent ou déjà bloqué dans cette direction.
    bool deplacer(Pion pion, Directions direction);

private:
    std::array<std::array<Case, TAILLE>, TAILLE> cases;  // cases[y][x]
};

#endif
