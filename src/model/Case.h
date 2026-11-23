#ifndef CASE_H
#define CASE_H

#include "Cible.h"
#include "Directions.h"
#include "Pion.h"
#include <array>
#include <optional>

class Case {
public:
    Case(int x = 0, int y = 0) : x(x), y(y) {}

    int getX() const { return x; }
    int getY() const { return y; }
    bool aMur(Directions direction) const { return murs.at(direction); }

    bool contientPion() const { return pion.has_value(); }
    bool contientCible() const { return cible.has_value(); }
    const std::optional<Pion>& getPion() const { return pion; }
    const std::optional<Cible>& getCible() const { return cible; }
    bool cibleAtteinte() const {
        return pion && cible && pion->doitAllerCible(*cible);
    }

private:
    friend class Plateaux;  // Le plateau synchronise les murs entre deux cases.
    int x;
    int y;
    std::array<bool, 4> murs{};
    std::optional<Pion> pion;
    std::optional<Cible> cible;
};

#endif
