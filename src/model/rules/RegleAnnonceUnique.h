#ifndef REGLEANNONCEUNIQUE_H
#define REGLEANNONCEUNIQUE_H

#include "Rule.h"

class RegleAnnonceUnique : public Rule{
    bool estApplicable(Jeux& jeux, Coup& coup) override;
    /**
     * @brief Le joueur annonce seulement une fois par tour.
     */
    bool validate(Jeux&, Coup& coup) override;
};
#endif