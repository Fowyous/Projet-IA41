#include "Pion.h"

#include "Cible.h"
#include <stdexcept>

Pion::Pion(Couleur couleur) : couleur(couleur) {
    if (couleur == Couleur::MULTICOLORE) {
        throw std::invalid_argument("Seule une cible peut être multicolore.");
    }
}

bool Pion::doitAllerCible(const Cible& cible) const {
    return cible.estBut()
        && (cible.getCouleur() == couleur || cible.getCouleur() == Couleur::MULTICOLORE);
}
