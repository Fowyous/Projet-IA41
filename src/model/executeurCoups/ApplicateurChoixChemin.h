#include "ApplicateurCoup.h"

class ApplicateurChoixChemin  : public ApplicateurCoup{
    /**
     * @brief On applique le chemin choisi au plateau.
     * 
     */
    void appliquer(Coup& coup, Jeux& jeux) override;
};