#include "ApplicateurCoup.h"

class ApplicateurChoixNbMouves : public ApplicateurCoup{

    void appliquer(Coup& coup, Jeux& jeux) override;
};