#ifndef PLATEAUX_H
#define PLATEAUX_H

#include "Case.h"
#include <array>
#include <vector>

struct Destination {
    Directions direction;
    int x;
    int y;
};

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
    // A implementer seulement par l'executeur de coups.
    bool deplacer(Pion pion, Directions direction);

    /**
     * @brief Calcule les destinations possibles pour un pion placé en (x, y).
     * Le plateau n'est pas modifié : il s'agit d'une simulation pour anticiper les coups.
     * La position (x, y) peut être hypothétique, il n'est pas nécessaire qu'un pion s'y trouve.
     * Pour chaque direction, le pion glisse jusqu'à un mur ou un autre pion.
     * Une direction n'est pas renvoyée si le pion ne peut pas bouger dans cette direction.
     *
     * @param x Position x de départ simulée
     * @param y Position y de départ simulée
     * @return std::vector<Destination> Les destinations possibles, chacune avec la direction
     * du déplacement et la case d'arrivée (x, y).
     */
    std::vector<Destination> destinationsPossibles(int x, int y) const;

private:
    std::array<std::array<Case, TAILLE>, TAILLE> cases;  // cases[y][x]
};

#endif
