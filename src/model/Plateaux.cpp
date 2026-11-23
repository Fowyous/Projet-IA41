#include "Plateaux.h"

#include <stdexcept>

namespace {
struct Pas {
    int dx;
    int dy;
    Directions opposee;
};

Pas pasPour(Directions direction) {
    switch (direction) {
        case NORD:  return { 0, -1, SUD};
        case EST:   return { 1,  0, OUEST};
        case SUD:   return { 0,  1, NORD};
        case OUEST: return {-1,  0, EST};
    }
    throw std::invalid_argument("Direction inconnue.");
}
}

Plateaux::Plateaux() {
    for (int y = 0; y < TAILLE; ++y) {
        for (int x = 0; x < TAILLE; ++x) {
            Case& cellule = cases[y][x];
            cellule = Case(x, y);
            cellule.murs[NORD] = (y == 0);
            cellule.murs[SUD] = (y == TAILLE - 1);
            cellule.murs[OUEST] = (x == 0);
            cellule.murs[EST] = (x == TAILLE - 1);
        }
    }
}

const Case& Plateaux::getCase(int x, int y) const {
    return cases.at(y).at(x);
}

void Plateaux::ajouterMur(int x, int y, Directions direction) {
    Case& cellule = cases.at(y).at(x);
    const Pas pas = pasPour(direction);
    if (cellule.aMur(direction)) {
        return;  // Inclut les bords, qui n'ont pas de case voisine.
    }
    Case& voisine = cases[y + pas.dy][x + pas.dx];
    cellule.murs[direction] = true;
    voisine.murs[pas.opposee] = true;
}

void Plateaux::placerCible(int x, int y, Cible cible) {
    cases.at(y).at(x).cible = cible;
}

const Case* Plateaux::trouverPion(Couleur couleur) const {
    for (const auto& ligne : cases) {
        for (const Case& cellule : ligne) {
            if (cellule.pion && cellule.pion->getCouleur() == couleur) {
                return &cellule;
            }
        }
    }
    return nullptr;
}

bool Plateaux::placerPion(int x, int y, Pion pion) {
    Case& cellule = cases.at(y).at(x);
    if (cellule.contientPion() || trouverPion(pion.getCouleur())) {
        return false;
    }
    cellule.pion = pion;
    return true;
}

bool Plateaux::deplacer(Pion pion, Directions direction) {
    const Case* depart = trouverPion(pion.getCouleur());
    if (!depart) {
        return false;
    }

    const Pas pas = pasPour(direction);
    int x = depart->getX();
    int y = depart->getY();
    while (!cases[y][x].aMur(direction)) {
        const int suivantX = x + pas.dx;
        const int suivantY = y + pas.dy;
        if (cases[suivantY][suivantX].contientPion()) {
            break;
        }
        x = suivantX;
        y = suivantY;
    }

    if (x == depart->getX() && y == depart->getY()) {
        return false;
    }
    cases[y][x].pion = pion;
    cases[depart->getY()][depart->getX()].pion.reset();
    return true;
}
