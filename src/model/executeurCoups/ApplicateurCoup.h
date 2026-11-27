#ifndef APPLICATEURCOUP_H
#define APPLICATEURCOUP_H

#include "../Coup.h"
#include "../Jeux.h"

class ApplicateurCoup{
    public:
    /**
     * @brief appliquer un coup après qu'il soit validé
     * 
     * appliquer un coup par rapport a chaque type de coups possible.(choisir nb mouves, choisir chemin).
     * Il est important de valider le coup avant de l'appliquer car cela n'est pas fait par cette methode.
     * 
     * @param coup Le coup qu'on veut appliquer
     * @param jeux 
     */
    virtual void appliquer(Coup& coup, Jeux& jeux) = 0;
    virtual ~ApplicateurCoup() = default;
};

#endif