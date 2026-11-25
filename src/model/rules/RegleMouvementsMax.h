#ifndef REGLESMOUVEMENTSMAX_H
#define REGLESMOUVEMENTSMAX_H

#include "Rule.h"

class RegleMouvementsMax : public Rule{
    bool estApplicable(Jeux& jeux, Coup& coup) override;
    /**
     * @brief Le joueur qui joue ne doit pas depasser le nombre de mouvements qu'il a dit qu'il fera.
     */
    bool validate(Jeux&, Coup& coup) override;
};
#endif