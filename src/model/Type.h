#ifndef TYPE_H
#define TYPE_H

enum Type {
    choixNombreMouves,  // Nom utilisé dans Coup.cpp pour l'annonce du joueur.
    choixRoute,
    attendreTour,
    choixTemps = choixNombreMouves  // Même phase, appelée « choix temps » sur le schéma.
};

#endif
