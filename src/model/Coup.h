#include <vector>
#include "Joueur.h"
#include "Type.h"
#include "Directions.h"
class Coup{
    private:
    Joueur joueur;
    Type type;
    int NbMouves;
    std::vector<Directions> chemin;
    public:
    void coupChoixNbMouves(Joueur joueur, int nombre);
    void coupChoixRoute(Joueur joueur, const std::vector<Directions> chemin);


};