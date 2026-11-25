#ifndef RULE_H
#define RULE_H

class Jeux;
class Coup;
class RuleEngine;

class Rule{
    friend class RuleEngine;
    private:

    /**
     * @brief  verifie si la regle est conserné par le coup 
     * 
     * @param jeuax Le jeux en cours.
     * @param coup un coup qu'on veut valider.
     * @return true la régle est applicable. Ce qui veut dire qu'elle concerne le coup qu'on veut valider. Cela ne veut pas dire qu'elle est validé.
     * @return false la régle ne concerne pas le jeux. On ne peux ni la valider ni la refuter.
     */
    virtual bool estApplicable(Jeux& jeux, Coup& coup) = 0;
    /**
     * @brief verifie si le coup respecte la regle.
     * 
     * @param jeux Le jeux en cours.
     * @param coup un coup qu'on veut valider.
     * @return true Le coup respecte la régle.
     * @return false Le coup ne respecte pas la régle.
     */
    virtual bool validate(Jeux& jeux, Coup& coup) = 0;

    public:
    virtual ~Rule() = default;
};

#endif