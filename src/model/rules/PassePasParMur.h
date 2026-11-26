#ifndef PASSEPASPARMUR_H
#define PASSEPASPARMUR_H

#include "Rule.h"

class PassePasParMur : public Rule {
public:
    // Une annonce de nombre de mouvements ne contient aucun trajet à vérifier.
    bool estApplicable(Jeux& jeux, Coup& coup) override;
    bool validate(Jeux& jeux, Coup& coup) override;
};

#endif
