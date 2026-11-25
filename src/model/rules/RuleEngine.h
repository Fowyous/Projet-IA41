#ifndef RULEENGINE_H
#define RULEENGINE_H

#include <vector>

class Rule;
class Jeux;
class Coup;

class Jeux;// pour eviter les boucles d'includes

/**
 * @brief Résultat de la vérification d'un coup par la liste de règles.
 * 
 */
struct ResultatVerification{
    bool valide;
    const Rule* regleViolee; // premiere regle violee, nullptr si valide
};
class RuleEngine{
    private :
    std::vector<Rule*> rules;

    public:
    ~RuleEngine();
    void addRule(Rule& rule);

    /**
     * @brief verifie la validité du coup selon tout les regles existants.
     * Pour chaque regle verifie d'abord son applicabilité, puis sa validité.
     * S'arrête à la première règle applicable qui n'est pas respectée.
     * 
     * @param jeux Le jeux en cours.
     * @param coup Le coup qu'on veut valider.
     */
    ResultatVerification validate(Jeux& jeux, Coup& coup);

};

#endif