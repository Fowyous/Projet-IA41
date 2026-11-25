#ifndef REGLEMOINSDUPLUSFAIBLE_H
#define REGLEMOINSDUPLUSFAIBLE_H

#include "Rule.h"
class RegleMoinsDuPlusFaible : Rule{
    bool estApplicable(Jeux& jeux, Coup& coup) override;
    /**
     * @brief Le nombres de mouves proposés par le joueur doit etre plus faible de celui qui le precede.
     */
    bool validate(Jeux& jeux, Coup& coup) override;
};
#endif