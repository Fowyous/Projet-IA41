#include "PassePasParMur.h"
#include "../Jeux.h"

bool PassePasParMur::estApplicable(Jeux&, Coup& coup) {
    return coup.type == Type::choixRoute;
}

bool PassePasParMur::validate(Jeux& jeux, Coup& coup) {
    // On enchaîne les glissades sur une copie pour préserver la position réelle du pion.
    Plateaux simulation = jeux.getPlateau();
    for (Directions direction : coup.chemin) {
        // Arriver contre un mur est permis. Repartir vers ce même mur bloque le coup.
        if (!simulation.deplacer(coup.pion, direction)) {
            return false;
        }
    }
    return true;
}
