#include <vector>
#include "Joueur.h"
#include "Type.h"
class Tour{
    private:
    int nbTour;
    std::vector<Joueur> joueurs;//la liste des joueurs ordonnés par qui passe en premier. 
    int ciblex, cibley;
    Type etat;//soit en mode choix temps soit en mode choix route ou les joueurs vont passer par leurs ordre dans la liste.
    public:
    

};